#include "AbstractCommand.h"


CommandData::CommandData() :
    pause_msecs(0),
    event(0)
{
}

CommandData::CommandData(QEvent* ev, const QString& nameString, const unsigned int pause):
    pause_msecs(pause),
    event(ev),
    objNameString(nameString)
{
}

bool CommandData::isValid() const
{
    return ((event != 0) && (!objNameString.isEmpty()));
}


AbstractCommand::AbstractCommand(QObject *parent)
	: QObject(parent)
{

}

AbstractCommand::~AbstractCommand()
{

}

QTime AbstractCommand::m_lastEventTime    = QTime();
QTime AbstractCommand::m_mouseMoveTime    = QTime();
QTime AbstractCommand::m_mousePressTime   = QTime();
QTime AbstractCommand::m_mouseReleaseTime = QTime();


void AbstractCommand::clearTimers()
{
    m_lastEventTime.start();
    m_mouseMoveTime.start();
//    m_mousePressTime.start();
//    m_mouseReleaseTime.start();

//    m_lastEventTime    = QTime();
//    m_mouseMoveTime    = QTime();
//    m_mousePressTime   = QTime();
//    m_mouseReleaseTime = QTime();
}

unsigned int AbstractCommand::getPauseMSecs()
{
    return m_lastEventTime.elapsed();
//    return m_lastEventTime.secsTo(QTime::currentTime());
}

void AbstractCommand::recordLastEventTime()
{
    m_lastEventTime.start();
//    m_lastEventTime.secsTo(QTime::currentTime());
}
