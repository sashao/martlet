#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H

#include <QObject>
#include <QEvent>

class AbstractCommand : public QObject
{
	Q_OBJECT

public:
	AbstractCommand(QObject *parent);
	~AbstractCommand();

	/// Return true iff this instance can be deserialized from this string.
	virtual bool canDeserialize(const QString commanStr) = 0;
	
	virtual QString record(const QEvent* event,const QString& objNameString) = 0;
	/// Returns True if success.
	virtual bool exec() = 0;

	virtual AbstractCommand* deserialize(const QString commanStr) = 0;
	
	virtual QEvent::Type type() = 0;
private:
	
};

#endif // ABSTRACTCOMMAND_H
