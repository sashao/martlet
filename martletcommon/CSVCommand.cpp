#include "CSVCommand.h"
#include <QString>
#include <QEvent>
#include <QMouseEvent>







CSVCommand::CSVCommand(QObject *parent)
	: AbstractCommand(parent)
{

}

void CSVCommand::fillDataFromList(CommandData& data, QStringList& list) const
{
    Q_ASSERT(list.count()==5);
    data.pause_msecs = list.at(1).toUInt();
    data.objNameString = list.at(4);
    QPoint pos(list.at(2).toInt(), list.at(3).toInt());

//	QMouseEvent* me = new QMouseEvent(QEvent::MouseButtonPress,QPoint(5,5), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QMouseEvent* me = new QMouseEvent(type(), pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    data.event = me;
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

CommandData CSVMousePressCommand::deserialize(const QString commanStr)
{
    CommandData returnData;
    if (commanStr.startsWith("MousePress")) {
        QStringList items = commanStr.split(',');
        fillDataFromList(returnData, items);
    }
    return returnData;
}

QEvent::Type CSVMousePressCommand::type() const
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

CommandData CSVMouseReleaseCommand::deserialize(const QString commanStr)
{
    CommandData returnData;
    if (commanStr.startsWith("MouseRelease")) {
        QStringList items = commanStr.split(',');
        fillDataFromList(returnData, items);
    }
    return returnData;
}
	
QEvent::Type CSVMouseReleaseCommand::type() const
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

CommandData CSVMouseMoveCommand::deserialize(const QString commanStr)
{
    CommandData returnData;
    if (commanStr.startsWith("MouseMove")) {
        QStringList items = commanStr.split(',');
        fillDataFromList(returnData, items);
    }
    return returnData;
}
	
QEvent::Type CSVMouseMoveCommand::type() const
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

CommandData CSVMouseEnterCommand::deserialize(const QString commanStr)
{
    CommandData returnData;
    if (commanStr.startsWith("MouseEnter")) {
        QStringList items = commanStr.split(',');
        fillDataFromList(returnData, items);
    }
    return returnData;
}
	
QEvent::Type CSVMouseEnterCommand::type() const
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

CommandData CSVMouseLeaveCommand::deserialize(const QString commanStr)
{
    CommandData returnData;
    if (commanStr.startsWith("MouseLeave")) {
        QStringList items = commanStr.split(',');
        fillDataFromList(returnData, items);
    }
    return returnData;
}
	
QEvent::Type CSVMouseLeaveCommand::type() const
{
	return QEvent::Leave;
}





