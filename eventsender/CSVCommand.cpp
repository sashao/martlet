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

QString CSVMousePressCommand::record(const QEvent* event, const QString& objNameString)
{
	const QMouseEvent* me = static_cast<const QMouseEvent*>(event);
	if (me) {
		return QString("Press,%1,%2,%3").arg(me->x()).arg(me->y()).arg(objNameString);
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

QString CSVMouseReleaseCommand::record(const QEvent* event, const QString& objNameString)
{
	const QMouseEvent* me = static_cast<const QMouseEvent*>(event);
	if (me) {
		return QString("Release,%1,%2,%3").arg(me->x()).arg(me->y()).arg(objNameString);
	}
	return QString();
}
	
QEvent::Type CSVMouseReleaseCommand::type()
{
	return QEvent::MouseButtonRelease;
}
