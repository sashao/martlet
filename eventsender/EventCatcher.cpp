#include "EventCatcher.h"
#include "AbstractEventFabric.h"
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
	QApplication::instance()->installEventFilter(this);
}

void EventCatcher::stopRecording()
{
	QApplication::instance()->removeEventFilter(this);
}

bool EventCatcher::eventFilter(QObject *obj, QEvent *ev)
{
	QString str(AbstractEventFabric::instance()->recordEvent(ev, obj));
	if (!str.isNull()) {
		qDebug(qPrintable(str));
	}
	return false;
}