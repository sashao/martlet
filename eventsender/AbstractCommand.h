#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H

#include <QObject>

class AbstractCommand : public QObject
{
	Q_OBJECT

public:
	AbstractCommand(QObject *parent);
	~AbstractCommand();

	virtual void canDeserialize(const QString commanStr);
	virtual void exec();

private:
	
};

#endif // ABSTRACTCOMMAND_H
