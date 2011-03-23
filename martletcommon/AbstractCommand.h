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


#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H

#include <QObject>
#include <QEvent>
#include <QTime>
/**
 *  Data needed to record and play single event basic params
 */
class CommandData // : public QSharedData
{
public:
    CommandData();
    CommandData(QEvent* event, const QString& nameString, const unsigned int pause);
    bool isValid() const;

    unsigned int pause_msecs;
    QEvent* event;
    QString objNameString;
};

class AbstractCommand : public QObject
{
	Q_OBJECT

public:
	AbstractCommand(QObject *parent);
	~AbstractCommand();

	/// Return true if this instance can be deserialized from this string.
	virtual bool canDeserialize(const QString commanStr) = 0;
	
	virtual QString record(const CommandData& data) = 0;

	virtual CommandData deserialize(const QString commanStr) = 0;
	
	virtual QEvent::Type type() const = 0;

    static void clearTimers();
    static unsigned int getPauseMSecs();
    
    static void recordLastEventTime();

protected:
    static QTime m_lastEventTime;
    static QTime m_mouseMoveTime;
    static QTime m_mousePressTime;
    static QTime m_mouseReleaseTime;
};




#endif // ABSTRACTCOMMAND_H
