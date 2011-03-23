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



#ifndef __PROJECT_SETTINGS_DIALOG_H__
#define __PROJECT_SETTINGS_DIALOG_H__


#include <QDialog>
#include <QPointer>
#include <QAbstractButton>


namespace Ui
{
    class ProjectSettingsDialog;
}


class ProjectSettingsDialog : public QDialog
{
Q_OBJECT
public:
	ProjectSettingsDialog( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~ProjectSettingsDialog();

protected slots:
	virtual void reject();
	virtual void accept();
	void apply();
	void init();

	void on_filterLineEdit_textChanged(const QString&);
	void on_projectNameLineEdit_textChanged(const QString&);
	void on_projectPathLineEdit_textChanged(const QString&);
	void on_projectTypeComboBox_activated(const QString&);
	void on_buttonBox_helpRequested();
	void on_buttonBox_clicked(QAbstractButton*);

private:
	Ui::ProjectSettingsDialog* m_ui;
};


#endif //__PROJECT_SETTINGS_DIALOG_H__
