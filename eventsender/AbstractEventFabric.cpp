#include "AbstractEventFabric.h"

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
	if (m_commandMap.contains(event->type())){
		AbstractCommand* command = m_commandMap.value(event->type());
		return command->record(event);
	}
	qDebug("AbstractEventFabric::recordEvent: Event wasn't recorded");
	return QString();
}

QEvent* AbstractEventFabric::deserializeEvent(const QString& commandStr)
{
	return 0;
}

void AbstractEventFabric::registerCommand(AbstractCommand* command)
{
	m_commandMap.insert(command->type(), command);
}

