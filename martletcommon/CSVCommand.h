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


#ifndef CSVCOMMAND_H
#define CSVCOMMAND_H

#include "AbstractCommand.h"
#include <QStringList>

class CSVCommand : public AbstractCommand
{
	Q_OBJECT

public:
	CSVCommand(QObject *parent);

	virtual bool canDeserialize(const QString ){ return false; }

protected:
        void fillMouseDataFromList(CommandData& data, QStringList& list) const;
        void fillKeyDataFromList(CommandData& data, QStringList& list) const;
};


class CSVMousePressCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMousePressCommand(QObject *parent);

	virtual QString record(const CommandData& data);
    virtual CommandData deserialize(const QString commanStr);
	
	virtual QEvent::Type type() const;
};



class CSVMouseReleaseCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMouseReleaseCommand(QObject *parent);

	virtual QString record(const CommandData& data);
    virtual CommandData deserialize(const QString commanStr);
	
	virtual QEvent::Type type() const;
};



class CSVMouseMoveCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMouseMoveCommand(QObject *parent);

	virtual QString record(const CommandData& data);
    virtual CommandData deserialize(const QString commanStr);
	
	virtual QEvent::Type type() const;
};




class CSVMouseEnterCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMouseEnterCommand(QObject *parent);

	virtual QString record(const CommandData& data);
    virtual CommandData deserialize(const QString commanStr);
	
	virtual QEvent::Type type() const;
};





class CSVMouseLeaveCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMouseLeaveCommand(QObject *parent);

	virtual QString record(const CommandData& data);
    virtual CommandData deserialize(const QString commanStr);
	
	virtual QEvent::Type type() const;
};



class CSVKeyPressCommand : public CSVCommand
{
    Q_OBJECT
public:
    CSVKeyPressCommand(QObject *parent);
    virtual QString record(const CommandData& data);
    virtual CommandData deserialize(const QString commanStr);
    virtual QEvent::Type type() const;
};


class CSVKeyReleaseCommand : public CSVCommand
{
    Q_OBJECT
public:
    CSVKeyReleaseCommand(QObject *parent);
    virtual QString record(const CommandData& data);
    virtual CommandData deserialize(const QString commanStr);
    virtual QEvent::Type type() const;
};





#endif // CSVCOMMAND_H
