#ifndef CSVCOMMAND_H
#define CSVCOMMAND_H

#include "AbstractCommand.h"

class CSVCommand : public AbstractCommand
{
	Q_OBJECT

public:
	CSVCommand(QObject *parent);

	virtual bool canDeserialize(const QString commanStr){ return false; }
	
	virtual bool exec(){ return false;}

    virtual CommandData deserialize(const QString commanStr){ return CommandData();}
};


class CSVMousePressCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMousePressCommand(QObject *parent);

	virtual QString record(const CommandData& data);
	
	virtual QEvent::Type type();
};



class CSVMouseReleaseCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMouseReleaseCommand(QObject *parent);

	virtual QString record(const CommandData& data);
	
	virtual QEvent::Type type();
};



class CSVMouseMoveCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMouseMoveCommand(QObject *parent);

	virtual QString record(const CommandData& data);
	
	virtual QEvent::Type type();
};




class CSVMouseEnterCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMouseEnterCommand(QObject *parent);

	virtual QString record(const CommandData& data);
	
	virtual QEvent::Type type();
};





class CSVMouseLeaveCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMouseLeaveCommand(QObject *parent);

	virtual QString record(const CommandData& data);
	
	virtual QEvent::Type type();
};






#endif // CSVCOMMAND_H
