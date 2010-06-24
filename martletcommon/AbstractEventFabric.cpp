#include "AbstractEventFabric.h"

#include "ObjectNameMapper.h"

#include <QThread>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>

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
    CommandData data = deserializeEvent(commandStr);
    // Sanity check
    if (!data.isValid()) {
        qWarning("Error Deserializating '%s'", qPrintable(commandStr));
        return;
    }

    QObject* widget = m_pNameMapper->getObjectFromName(data.objNameString);
    if (data.isValid() && (widget != 0)) {
        QTime timer;
        timer.start();
        const unsigned int pause = 8;
        if ( pause < data.pause_msecs ) {
            int delta =  data.pause_msecs /*- timer.elapsed()*/;
            while ( delta > 0 ) {
                usleep(qMin((int)pause, delta));
                QApplication::processEvents();
                delta = data.pause_msecs - timer.elapsed();
            }
        }
        
        const QWidget* w = qobject_cast<QWidget *>(widget);
        const QMouseEvent* me = static_cast<QMouseEvent* >(data.event);
        if (w && me) 
        {
            const QPoint mpos(w->mapToGlobal(me->pos()));
            QCursor::setPos(mpos);
        }
        if (data.event->type() != QEvent::MouseMove)
        {
            QApplication::sendEvent(widget, data.event);
        }
    } else {
        qDebug("Something went wrong while string decoding. (event = %d, object= %d)", long(data.event), long(widget));
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

