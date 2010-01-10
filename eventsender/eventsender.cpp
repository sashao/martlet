#include "eventsender.h"
#include <QApplication>
#include <QMouseEvent>
#include <QKeyEvent>

eventsender::eventsender(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

eventsender::~eventsender()
{

}


void eventsender::on_checkBox_clicked(bool)
{
	qDebug("eventsender::on_checkBox_clicked(bool)");
}

void eventsender::on_pushButton_clicked()
{
	qDebug("eventsender::on_pushButton_clicked()");
	QMouseEvent* me = new QMouseEvent(QEvent::MouseButtonPress,QPoint(5,5), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QApplication::sendEvent(ui.checkBox, me);
	QMouseEvent* me2 = new QMouseEvent(QEvent::MouseButtonRelease,QPoint(5,5), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QApplication::sendEvent(ui.checkBox, me2);
}