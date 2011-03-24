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
