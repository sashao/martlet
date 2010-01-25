#include "EventCatcher.h"
#include "AbstractEventFabric.h"
#include "AbstractCommand.h"
#include <QApplication>

EventCatcher::EventCatcher(QObject *parent)
	: QObject(parent)
{

}

EventCatcher::~EventCatcher()
{

}

void EventCatcher::startRecording()
{
    AbstractCommand::clearTimers();
	QApplication::instance()->installEventFilter(this);
}

void EventCatcher::stopRecording()
{
	QApplication::instance()->removeEventFilter(this);
}

bool EventCatcher::eventFilter(QObject *obj, QEvent *ev)
{
    if (ev->spontaneous()) 
    {
	    QString str(AbstractEventFabric::instance()->recordEvent(ev, obj));
	    if (!str.isNull()) {
		    qDebug(qPrintable(str));
	    }
    }
	return false;
}