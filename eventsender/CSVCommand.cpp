#include "CSVCommand.h"
#include <QString>
#include <QEvent>
#include <QMouseEvent>






CSVCommand::CSVCommand(QObject *parent)
	: AbstractCommand(parent)
{

}









CSVMousePressCommand::CSVMousePressCommand(QObject *parent)
	: CSVCommand(parent)
{
}

QString CSVMousePressCommand::record(const CommandData& data)
{
	const QMouseEvent* me = static_cast<const QMouseEvent*>(data.event);
	if (me) {
        return QString("MousePress,%1,%2,%3,%4").arg(data.pause_msecs).arg(me->x()).arg(me->y()).arg(data.objNameString);
    } else {
        qDebug("NOT AN QMouseEvent");
    }
	return QString();
}
	
QEvent::Type CSVMousePressCommand::type()
{
	return QEvent::MouseButtonPress;
}








CSVMouseReleaseCommand::CSVMouseReleaseCommand(QObject *parent)
	: CSVCommand(parent)
{
}

QString CSVMouseReleaseCommand::record(const CommandData& data)
{
	const QMouseEvent* me = static_cast<const QMouseEvent*>(data.event);
	if (me) {
		return QString("MouseRelease,%1,%2,%3,%4").arg(data.pause_msecs).arg(me->x()).arg(me->y()).arg(data.objNameString);
    } else {
        qDebug("NOT AN QMouseEvent");
    }
	return QString();
}
	
QEvent::Type CSVMouseReleaseCommand::type()
{
	return QEvent::MouseButtonRelease;
}









CSVMouseMoveCommand::CSVMouseMoveCommand(QObject *parent)
	: CSVCommand(parent)
{
}

QString CSVMouseMoveCommand::record(const CommandData& data)
{
	const QMouseEvent* me = static_cast<const QMouseEvent*>(data.event);
	if (me) {
		return QString("MouseMove,%1,%2,%3,%4").arg(data.pause_msecs).arg(me->x()).arg(me->y()).arg(data.objNameString);
    } else {
        qDebug("NOT AN QMouseEvent");
    }
	return QString();
}
	
QEvent::Type CSVMouseMoveCommand::type()
{
	return QEvent::MouseMove;
}









CSVMouseEnterCommand::CSVMouseEnterCommand(QObject *parent)
	: CSVCommand(parent)
{
}

QString CSVMouseEnterCommand::record(const CommandData& data)
{
	const QMouseEvent* me = static_cast<const QMouseEvent*>(data.event);
	if (me) {
		return QString("MouseEnter,%1,%2,%3,%4").arg(data.pause_msecs).arg(me->x()).arg(me->y()).arg(data.objNameString);
	}
	return QString();
}
	
QEvent::Type CSVMouseEnterCommand::type()
{
	return QEvent::Enter;
}










CSVMouseLeaveCommand::CSVMouseLeaveCommand(QObject *parent)
	: CSVCommand(parent)
{
}

QString CSVMouseLeaveCommand::record(const CommandData& data)
{
	const QMouseEvent* me = static_cast<const QMouseEvent*>(data.event);
	if (me) {
		return QString("MouseLeave,%1,%2,%3,%4").arg(data.pause_msecs).arg(me->x()).arg(me->y()).arg(data.objNameString);
	}
	return QString();
}
	
QEvent::Type CSVMouseLeaveCommand::type()
{
	return QEvent::Leave;
}





