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
    void fillDataFromList(CommandData& data, QStringList& list) const;
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
