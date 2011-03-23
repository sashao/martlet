//    Martlet - application automated Qt GUI application testing and more.
//    Copyright (C) 2010  Oleksandr Omelchuk sashao@e-mail.ua

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
        , m_blockSpontaneous(false)
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

void EventCatcher::blockSpontaneousEvents(const bool block)
{
    m_blockSpontaneous = block;
}

bool EventCatcher::eventFilter(QObject *obj, QEvent *event)
{
    if (m_blockSpontaneous && event->spontaneous() && (
                               event->type() == QEvent::MouseMove ||
                               event->type() == QEvent::MouseButtonPress ||
                               event->type() == QEvent::MouseButtonRelease ))
    {
        // block spontaneous mouse move events during playback
        return true;
    }

    {
        if ( event->type() == QEvent::MouseButtonPress ) {
            QMouseEvent *me = static_cast<QMouseEvent *>(event);
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
        }
        QString str(AbstractEventFabric::instance()->recordEvent(event, obj));
        if (!str.isNull()) {
            qDebug("Event type %d - '%s'", event->type(), qPrintable(str));
        }
    }
    return false;
}
