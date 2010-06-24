#include "filter.h"
#include "qspywidget.h"


#include <QKeyEvent>
#include <QMessageBox>
#include <QCoreApplication>


int message()
{
	QMessageBox msgBox;
	msgBox.setText("The document has been modified.");
	msgBox.setInformativeText("Do you want to save your changes?");
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	return msgBox.exec();
}

filter::filter()
{
//	QSpyWidget::instance()->setObject(0);

	this->moveToThread(QCoreApplication::instance()->thread());

//	connect(this, SIGNAL(objChanged(QObject *)),
//			QSpyWidget::instance(), SLOT(setObject(QObject *)), Qt::QueuedConnection);

}

bool filter::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
//		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//		qDebug("Ate key press %d", keyEvent->key());
//		message();
		return false;
	}
	if (event->type() == QEvent::MouseMove)
	{
//		QMouseEvent *keyEvent = static_cast<QMouseEvent *>(event);
//		qDebug("Mouse move %d", keyEvent->pos().x());
		return false;
	}
	if (event->type() == QEvent::MouseButtonPress)
	{
//		QMouseEvent *keyEvent = static_cast<QMouseEvent *>(event);
//		qDebug("Mouse pres %d", keyEvent->pos().x());
		//QSpyWidget::instance()->setObject(obj);
		emit objChanged(obj);
		return false;
	}
	if (event->type() == QEvent::Show)
	{
		if (!QCoreApplication::startingUp ())
		{
			//QSpyWidget::instance()->show();
		}
		return false;
	}


//	else
	{                 // standard event processing
		return QObject::eventFilter(obj, event);
	}
}
