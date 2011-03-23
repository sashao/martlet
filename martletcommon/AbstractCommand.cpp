//    Martlet - application automated Qt GUI application testing and more.
//    Copyright (C) 2010  Oleksandr Omelchuk sashao@e-mail.ua

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
