#ifndef ABSTRACTEVENTFABRIC_H
#define ABSTRACTEVENTFABRIC_H

#include <QObject>
#include <QEvent>
#include <QString>
#include <QMap>
#include <QPair>

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

	virtual void registerCommand(AbstractCommand* command);

    inline QString getOutput() const;

    virtual void playSingleLineEvent(const QString& commandStr);

protected:
    CommandData deserializeEvent(const QString& commandStr);
    QObject* findObjectFromName(const QString& objNameStr);
    
    static AbstractEventFabric* m_instance;
    QString m_output;
private:

	TypeCommandMap m_commandMap;

};

QString AbstractEventFabric::getOutput() const
{
    return m_output;
}


#endif // ABSTRACTEVENTFABRIC_H
