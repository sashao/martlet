#include "widget.h"

#include <math.h>

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QList>

static const double pi2 = 2.0*M_PI;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
	angle.first = 0;
	angle.second = 0;
	myID = -1;

	const int num = 31;
	for (int i = 0; i<num; ++i)
	{
		items.push_back(QPointF(pi2 * qrand()/RAND_MAX, pi2 * 0.1 +0 * qrand()/RAND_MAX));
//		qDebug()<< pi2 * qrand()/RAND_MAX<< " / "<< pi2*0.1;
	}

	myID = startTimer(50);
}

Widget::~Widget()
{

}

void Widget::paintEvent ( QPaintEvent * event )
{
	QWidget::paintEvent(event);
	QPainter painter(this);
//	painter.fillRect(event->rect(), Qt::green);

	painter.drawEllipse(center, radius, radius);

	QPointF iter;
	foreach(iter, items)
	{
		drawItem(&painter, pointFromAngle(QPair<double, double> (iter.x()+angle.first, iter.y()+angle.second)));
	}
}

void Widget::resizeEvent (QResizeEvent * event )
{
	radius = qMin(event->size().height(), event->size().width())/2;
//	const int delta = event->size().width() - event->size().height();
	center.setX(event->size().width()/2);
	center.setY(event->size().height()/2);


	return QWidget::resizeEvent(event);
}

void Widget::timerEvent ( QTimerEvent * event )
{
	if (event->timerId() == myID)
	{
		angle.first = angle.first + M_PI*0.003;
		angle.second = angle.second + M_PI*0.0009;
		event->accept();
		repaint();
//		qDebug()<< angle.first;
	}
}

void Widget::drawItem(QPainter * painter, QPair<QPoint, double> param)
{
	const int rad = qRound(3* param.second);
//	painter->drawEllipse(param.first, rad, rad);
}

QPair<QPoint, double> Widget::pointFromAngle(QPair<double, double> angle) const
{
//	QPoint pos(sin(angle.second)*radius*sin(angle.first), cos(angle.first)*radius);
	QPoint pos(sin(angle.first)*radius*sin(angle.second), cos(angle.second)*radius*cos(angle.first));
	const double rad = 1;//cos(angle.second);
//	if (rad > 0) qDebug(">>>>");
//	else qDebug("<<<<");
	return QPair<QPoint, double>(pos+center, (rad+1)/2);
}






