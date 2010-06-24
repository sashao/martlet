#ifndef ABSTRACTEVENTFABRIC_H
#define ABSTRACTEVENTFABRIC_H

#include <QObject>
#include <QEvent>
#include <QString>
#include <QMap>
#include <QPair>

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

protected:
    CommandData deserializeEvent(const QString& commandStr);
    
    static AbstractEventFabric* m_instance;
    QString m_output;
private:

    TypeCommandMap m_commandMap;
    AbstractObjectNameMapper* m_pNameMapper;
};



#endif // ABSTRACTEVENTFABRIC_H
