#ifndef ABSTRACTEVENTFABRIC_H
#define ABSTRACTEVENTFABRIC_H

#include <QObject>
#include <QEvent>
#include <QString>

class AbstractCommand;

class AbstractEventFabric : public QObject
{
	Q_OBJECT

public:
	AbstractEventFabric(QObject *parent);
	~AbstractEventFabric();

	QString recordEvent(QEvent* event);
	QEvent* deserializeEvent(const QString& commandStr);

	void registerCommand(QEvent::Type type, AbstractCommand* command);

private:
	QAbstractCommand* commandFromEvent(QEvent* event);
	
};

#endif // ABSTRACTEVENTFABRIC_H
