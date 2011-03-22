#include "AbstractEventFabric.h"

#include "ObjectNameMapper.h"

#include <QThread>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QEventLoop>


AbstractEventFabric* AbstractEventFabric::m_instance = 0;

AbstractEventFabric::AbstractEventFabric(QObject *parent)
	: QObject(parent),
    m_pNameMapper( new ObjectNameMapper(this))
{
    m_output = "";
}

AbstractEventFabric::~AbstractEventFabric()
{

}

AbstractEventFabric* AbstractEventFabric::instance()
{
	return m_instance;
}

void AbstractEventFabric::setInstance(AbstractEventFabric* fabric)
{
	m_instance = fabric;
}


QString AbstractEventFabric::recordEvent(QEvent* event, QObject* obj )
{
    QString output;
    output.reserve(100);
	if (m_commandMap.contains(event->type())){
        AbstractCommand* command = m_commandMap.value(event->type());
        const QString uniqueObjName = m_pNameMapper->makeCachedObjectName(obj);
        CommandData data(event, uniqueObjName, AbstractCommand::getPauseMSecs());
        output = command->record( data );
        AbstractCommand::recordLastEventTime();
        m_output.append(output);
        m_output.append("\n");
	}
	return output;
}

void AbstractEventFabric::playSingleLineEvent(const QString& commandStr)
{
    // Omit empty strings
    if (commandStr.isEmpty()) return;

    if (commandStr.startsWith("VERIFY")) {
        emit startingTest(commandStr);
        QString result = "FAILED";
        const QStringList slist = commandStr.split(',');
        /// "VERIFY,widget,property,value"
        if ( slist.count()==4 )
        {
            QObject* widget = m_pNameMapper->getObjectFromName(slist[1]);
            if (widget)
            {
                const QString prop = slist[2];
                const QString value = slist[3];
                const QVariant actual = widget->property(qPrintable(prop));
                QVariant toCompare = QVariant::fromValue(value);
                toCompare.convert(actual.type());
                if(actual == toCompare && actual.isValid()) {
                    result = "PASSED";
                }
                result += actual.toString() + toCompare.toString();
            }
        }
        emit testFinished(commandStr, result);
        return;
    }

    CommandData data = deserializeEvent(commandStr);
    // Sanity check
    if (!data.isValid()) {
        qWarning("Error Deserializating '%s'", qPrintable(commandStr));
        return;
    }

    QObject* widget = m_pNameMapper->getObjectFromName(data.objNameString);
    if (data.isValid() && (widget != 0)) {


        static QEventLoop eventLoop;
        QTimer::singleShot(data.pause_msecs, &eventLoop, SLOT(quit()));
        eventLoop.exec();
        
        const QWidget* w = qobject_cast<QWidget *>(widget);
        if (w)
        {
            if (data.event && (
                    data.event->type() == QEvent::MouseMove ||
                    data.event->type() == QEvent::MouseButtonPress ||
                    data.event->type() == QEvent::MouseButtonRelease ) )
            {
                const QMouseEvent* me = static_cast<QMouseEvent* >(data.event);
                const QPoint mpos(w->mapToGlobal(me->pos()));
                QCursor::setPos(mpos);
            }
        }
        if (data.event->type() /*!= QEvent::MouseMove*/)
        {
            QApplication::sendEvent(widget, data.event);
        }

    } else {
        //qDebug("Something went wrong while string decoding. (event = %d, object= %d)",
        //       static_cast<int>(data.event->type()), reinterpret_cast<int>(widget) );
    }
}

void AbstractEventFabric::playAll(const QString& commandStrings)
{
    QStringList list = commandStrings.split('\n');
    QString line;
    foreach (line, list) {
        playSingleLineEvent(line);
    }
}

CommandData AbstractEventFabric::deserializeEvent(const QString& commandStr)
{
    CommandData result;
    CommandData data;
    qDebug("Deserialization of '%s'", qPrintable(commandStr));

    TypeCommandMap::const_iterator iter;
    for (iter = m_commandMap.constBegin(); iter != m_commandMap.constEnd(); ++iter)
    {
        CommandData data = iter.value()->deserialize(commandStr);
        if (data.isValid()) {
            result = data;
            break;
        }
    }
	return result;
}

void AbstractEventFabric::registerCommand(AbstractCommand* command)
{
	m_commandMap.insert(command->type(), command);
}

QString AbstractEventFabric::getOutput() const
{
    qDebug("AbstractEventFabric::getOutput(%d) ", m_output.size());
    return m_output;
}

