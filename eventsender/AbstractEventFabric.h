#ifndef ABSTRACTEVENTFABRIC_H
#define ABSTRACTEVENTFABRIC_H

#include <QObject>
#include <QEvent>
#include <QString>
#include <QMap>

#include "AbstractCommand.h"

typedef QMap<QEvent::Type, AbstractCommand*> TypeCommandMap;

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
	QEvent* deserializeEvent(const QString& commandStr);

	virtual void registerCommand(AbstractCommand* command);

protected:
		static AbstractEventFabric* m_instance;
private:
	virtual AbstractCommand* commandFromEvent(QEvent* event) = 0;

	TypeCommandMap m_commandMap;

};

#endif // ABSTRACTEVENTFABRIC_H
