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


#ifndef EVENTCATCHER_H
#define EVENTCATCHER_H

#include <QObject>

class EventCatcher : public QObject
{
	Q_OBJECT

public:
	EventCatcher(QObject *parent);
	~EventCatcher();

	void startRecording();
	void stopRecording();

        void (*m_spy)(QObject *);

        void blockSpontaneousEvents(const bool block);

private:
	bool eventFilter(QObject *obj, QEvent *ev);	
        bool m_blockSpontaneous;
};

#endif // EVENTCATCHER_H
