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


#ifndef QSPYFORM_H
#define QSPYFORM_H


#include "ui_qspyform.h"
#include <QWidget>


class QProcess;
class QSettings;


class QSpyForm : public QWidget , private Ui::qspyForm
{
Q_OBJECT
public:
	QSpyForm( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~QSpyForm();
protected slots:
	void on_spyGroup_toggled(bool);
	void on_appPathComboBox_activated(const QString&);
	void on_dirToolButton_clicked();
	void on_startStopPushButton_clicked();

protected:
	QString martexPath;
	QProcess *martexProc;
	QSettings* settings;

	bool startProcess();
	bool stopProcess();
	void setRunningState(QString message, QString appPath = "");
	void setStopState(QString message, bool isMsgLabelVisible = true, QString appPath = "");
};


#endif //QSPYFORM_H
