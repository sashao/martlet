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

	virtual AbstractCommand* deserialize(const QString commanStr){ return 0;}
};


class CSVMousePressCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMousePressCommand(QObject *parent);

	virtual QString record(const QEvent* event, const QString& objNameString);
	
	virtual QEvent::Type type();
};



class CSVMouseReleaseCommand : public CSVCommand
{
	Q_OBJECT

public:
	CSVMouseReleaseCommand(QObject *parent);

	virtual QString record(const QEvent* event, const QString& objNameString);
	
	virtual QEvent::Type type();
};


#endif // CSVCOMMAND_H
