#include "AbstractEventFabric.h"
#include <QThread>
#include <QApplication>
#include <QWidget>

AbstractEventFabric* AbstractEventFabric::m_instance = 0;

AbstractEventFabric::AbstractEventFabric(QObject *parent)
	: QObject(parent)
{

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
        // TODO: delegate this to separate obj_name_resolver class
        const QString uniqueObjName = obj->objectName();
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
    QPair<QEvent*, QObject*> pair = deserializeEvent(commandStr);
    if ((pair.first !=0) && (pair.second != 0)) {

    } else {
        qDebug("Something went wrong while string decoding. (event = %d, object= %d)", int(pair.first), int(pair.second));
    }
}


QPair<QEvent*, QObject*> AbstractEventFabric::deserializeEvent(const QString& commandStr)
{
    QPair<QEvent*, QObject*> result(0, 0);
    CommandData data;
    qDebug("Deserialization of '%s'", qPrintable(commandStr));
//    QThread::currentThread()->wait(30);
    // this loop sould be removed when following loop moved to Thread class.
    for (int i  = 0; i<= 50000; ++i) {
        QApplication::processEvents();
    }

    TypeCommandMap::const_iterator iter;
    for (iter = m_commandMap.constBegin(); iter != m_commandMap.constEnd(); ++iter)
    {
        CommandData data = iter.value()->deserialize(commandStr);
        if (data.isValid()) {
            result.first = data.event;
            result.second = findObjectFromName(data.objNameString);
            break;
        }
    }
	return result;
}

QObject* AbstractEventFabric::findObjectFromName(const QString& objNameStr)
{
    // TODO: delegate this to separate obj_name_resolver class
    QObject* obj = QApplication::activeWindow()->findChild<QObject*>(objNameStr);
    if (!obj) {
        qDebug("Unable to find object with name '%s'", qPrintable(objNameStr));
    }
    return obj;
}


void AbstractEventFabric::registerCommand(AbstractCommand* command)
{
	m_commandMap.insert(command->type(), command);
}

