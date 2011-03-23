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


#ifndef ABSTRACTEVENTFABRIC_H
#define ABSTRACTEVENTFABRIC_H

#include <QObject>
#include <QEvent>
#include <QString>
#include <QMap>
#include <QPair>
#include <QVariant>

#include "AbstractCommand.h"

typedef QMap<QEvent::Type, AbstractCommand*> TypeCommandMap;

class AbstractObjectNameMapper;

class AbstractEventFabric : public QObject
{
	Q_OBJECT

protected:
	AbstractEventFabric(QObject *parent);
	~AbstractEventFabric();
public:
	static AbstractEventFabric* instance();
	static void setInstance(AbstractEventFabric* fabric);

	virtual QString recordEvent(QEvent* event, QObject* obj);

	virtual void registerCommand(AbstractCommand* command);

    QString getOutput() const;

    virtual void playSingleLineEvent(const QString& commandStr);
    virtual void playAll(const QString& commandStrings);

signals:
    void startingTest(QVariant name);
    void testFinished(QVariant name, QVariant result);

protected:
    CommandData deserializeEvent(const QString& commandStr);
    
    static AbstractEventFabric* m_instance;
    QString m_output;
private:

    TypeCommandMap m_commandMap;
    AbstractObjectNameMapper* m_pNameMapper;
};



#endif // ABSTRACTEVENTFABRIC_H
