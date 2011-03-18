#include "EventCatcher.h"
#include "AbstractEventFabric.h"
#include "AbstractCommand.h"
#include <QApplication>
#include <QMouseEvent>
#include <QMetaProperty>
#include <QMessageBox>

EventCatcher::EventCatcher(QObject *parent)
	: QObject(parent)
        , m_spy(0)
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
            if (m_spy && ev->type() == QEvent::MouseButtonPress) {
                QMouseEvent *me = static_cast<QMouseEvent *>(ev);
                if (me->modifiers().testFlag(Qt::ControlModifier)) {
                    m_spy(obj);
                }

                if (me->modifiers().testFlag(Qt::ShiftModifier)) {
                    QString props ;
                    for (int i = 0; i <obj->metaObject()->propertyCount(); ++i )
                    {
                        const QMetaProperty mp = obj->metaObject()->property(i);
                        const QString nm = mp.name();
                        props.append(nm);
                        props.append(QString(qMax(30-nm.length(), 1), QChar(' ')));
                        props.append(',');
                        if (i%2 == 0) {
                            props.append('\n');
                        }
                    }
                    QMessageBox::information(0, obj->objectName(), props);
                }
                QString str(AbstractEventFabric::instance()->recordEvent(ev, obj));
                if (!str.isNull()) {
                qDebug("Event type %d - '%s'", ev->type(), qPrintable(str));
                }
            }
    }
	return false;
}
