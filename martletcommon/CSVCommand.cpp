#include "CSVCommand.h"
#include <QString>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>


CSVCommand::CSVCommand(QObject *parent)
	: AbstractCommand(parent)
{

}

void CSVCommand::fillMouseDataFromList(CommandData& data, QStringList& list) const
{
    Q_ASSERT(list.count()== 5+3);
    data.pause_msecs = list.at(1).toUInt();
    data.objNameString = list.at(4);
    QPoint pos(list.at(2).toInt(), list.at(3).toInt());

    const Qt::MouseButton mb = static_cast<Qt::MouseButton>(list.at(5).toInt());
    Qt::MouseButtons mbs;      mbs |= static_cast<Qt::MouseButton>(list.at(6).toInt());
    Qt::KeyboardModifiers kms; kms |= static_cast<Qt::KeyboardModifier>(list.at(7).toInt());

//    qDebug("construct mbuttons %d %d ", list.at(6).toInt(), int(mbs));

    QMouseEvent* me = new QMouseEvent(type(), pos, mb, mbs, kms);
    data.event = me;
}

void CSVCommand::fillKeyDataFromList(CommandData& data, QStringList& list) const
{
    Q_ASSERT(list.count()== 6);
    data.pause_msecs = list.at(1).toUInt();
    data.objNameString = list.at(5);

    const Qt::Key key = static_cast<Qt::Key>(list.at(2).toInt());
    Qt::KeyboardModifiers kms; kms |= static_cast<Qt::KeyboardModifier>(list.at(3).toInt());
    QString text;
    const QStringList sl  = list.at(4).split('|', QString::SkipEmptyParts);
    foreach (QString d, sl) {
        text.append(QChar(d.toUInt()));
    }

    QKeyEvent* me = new QKeyEvent(type(), key, kms, text);
    data.event = me;

}

QString modifiers(const QMouseEvent* me)
{
    return QString(",%1,%2,%3")
            .arg(static_cast<int>(me->button()))
            .arg(int(me->buttons()))
            .arg(int(me->modifiers()));
}



CSVMousePressCommand::CSVMousePressCommand(QObject *parent)
	: CSVCommand(parent)
{
}

QString CSVMousePressCommand::record(const CommandData& data)
{
	const QMouseEvent* me = static_cast<const QMouseEvent*>(data.event);
	if (me) {
        return QString("MousePress,%1,%2,%3,%4").arg(data.pause_msecs).arg(me->x()).arg(me->y()).arg(data.objNameString)+modifiers(me);
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
        fillMouseDataFromList(returnData, items);
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
        return QString("MouseRelease,%1,%2,%3,%4").arg(data.pause_msecs).arg(me->x()).arg(me->y()).arg(data.objNameString)+modifiers(me);
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
        fillMouseDataFromList(returnData, items);
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
        return QString("MouseMove,%1,%2,%3,%4").arg(data.pause_msecs).arg(me->x()).arg(me->y()).arg(data.objNameString)+modifiers(me);
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
        fillMouseDataFromList(returnData, items);
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
        return QString("MouseEnter,%1,%2,%3,%4").arg(data.pause_msecs).arg(me->x()).arg(me->y()).arg(data.objNameString)+modifiers(me);
	}
	return QString();
}

CommandData CSVMouseEnterCommand::deserialize(const QString commanStr)
{
    CommandData returnData;
    if (commanStr.startsWith("MouseEnter")) {
        QStringList items = commanStr.split(',');
        fillMouseDataFromList(returnData, items);
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
        return QString("MouseLeave,%1,%2,%3,%4").arg(data.pause_msecs).arg(me->x()).arg(me->y()).arg(data.objNameString)+modifiers(me);
	}
	return QString();
}

CommandData CSVMouseLeaveCommand::deserialize(const QString commanStr)
{
    CommandData returnData;
    if (commanStr.startsWith("MouseLeave")) {
        QStringList items = commanStr.split(',');
        fillMouseDataFromList(returnData, items);
    }
    return returnData;
}
	
QEvent::Type CSVMouseLeaveCommand::type() const
{
	return QEvent::Leave;
}



CSVKeyPressCommand::CSVKeyPressCommand(QObject *parent)
    : CSVCommand(parent)
{
}

QString CSVKeyPressCommand::record(const CommandData& data)
{
    const QKeyEvent* ke = static_cast<const QKeyEvent*>(data.event);
    if (ke) {
        QString text;
        text.reserve(20);
        for (int i = 0; i < ke->text().size(); ++i) {
            text.append( QString::number(ke->text().at(i).unicode())+ '|');
        }
        return QString("KeyPress,%1,%2,%3,%4,%5")
                .arg(data.pause_msecs)
                .arg(int(ke->key()))
                .arg(int(ke->modifiers()))
                .arg(text)
                .arg(data.objNameString);

    }
    return QString();
}

CommandData CSVKeyPressCommand::deserialize(const QString commanStr)
{
    CommandData returnData;
    if (commanStr.startsWith("KeyPress")) {
        QStringList items = commanStr.split(',');
        fillKeyDataFromList(returnData, items);
    }
    return returnData;
}

QEvent::Type CSVKeyPressCommand::type() const
{
    return QEvent::KeyPress;
}








CSVKeyReleaseCommand::CSVKeyReleaseCommand(QObject *parent)
    : CSVCommand(parent)
{
}

QString CSVKeyReleaseCommand::record(const CommandData& data)
{
    const QKeyEvent* ke = static_cast<const QKeyEvent*>(data.event);
    if (ke) {
        QString text;
        text.reserve(20);
        for (int i = 0; i < ke->text().size(); ++i) {
            text.append( QString::number(ke->text().at(i).unicode())+ '|');
        }
        return QString("KeyRelease,%1,%2,%3,%4,%5")
                        .arg(data.pause_msecs)
                        .arg(int(ke->key()))
                        .arg(int(ke->modifiers()))
                        .arg(text)
                        .arg(data.objNameString);
    }
    return QString();
}

CommandData CSVKeyReleaseCommand::deserialize(const QString commanStr)
{
    CommandData returnData;
    if (commanStr.startsWith("KeyRelease")) {
        QStringList items = commanStr.split(',');
        fillKeyDataFromList(returnData, items);
    }
    return returnData;
}

QEvent::Type CSVKeyReleaseCommand::type() const
{
    return QEvent::KeyRelease;
}
