#include "EventCatcher.h"
#include "AbstractEventFabric.h"

EventCatcher::EventCatcher(QObject *parent)
	: QObject(parent)
{

}

EventCatcher::~EventCatcher()
{

}

bool EventCatcher::eventFilter(QObject *obj, QEvent *ev)
{
	QString str(AbstractEventFabric::instance()->recordEvent(ev, obj));
	if (!str.isNull()) {
		qDebug(qPrintable(str));
	}
	return false;
}