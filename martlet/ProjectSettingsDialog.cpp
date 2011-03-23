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


#include "ProjectSettingsDialog.h"
#include "ui_ProjectSettingsDialog.h"


ProjectSettingsDialog::ProjectSettingsDialog( QWidget * parent, Qt::WindowFlags f) : QDialog(parent,f)
{
	m_ui = new Ui::ProjectSettingsDialog;
	m_ui->setupUi(this);

	init();
}

ProjectSettingsDialog::~ProjectSettingsDialog()
{
    delete m_ui;
}

void ProjectSettingsDialog::init()
{
	qWarning("TODO: %s %d",__FILE__,__LINE__);
}

void ProjectSettingsDialog::apply()
{
	qWarning("TODO: %s %d",__FILE__,__LINE__);
}

void ProjectSettingsDialog::reject()
{
	qWarning("TODO: %s %d",__FILE__,__LINE__);
	QDialog::reject();
}

void ProjectSettingsDialog::accept()
{
	qWarning("TODO: %s %d",__FILE__,__LINE__);
	QDialog::accept();
}

void ProjectSettingsDialog::on_filterLineEdit_textChanged(const QString&)
{
	qWarning("TODO: %s	%d",__FILE__,__LINE__);
}

void ProjectSettingsDialog::on_projectNameLineEdit_textChanged(const QString&)
{
	qWarning("TODO: %s	%d",__FILE__,__LINE__);
}

void ProjectSettingsDialog::on_projectPathLineEdit_textChanged(const QString&)
{
	qWarning("TODO: %s	%d",__FILE__,__LINE__);
}

void ProjectSettingsDialog::on_projectTypeComboBox_activated(const QString&)
{
	qWarning("TODO: %s	%d",__FILE__,__LINE__);
}

void ProjectSettingsDialog::on_buttonBox_helpRequested()
{
	qWarning("TODO: %s	%d",__FILE__,__LINE__);
}

void ProjectSettingsDialog::on_buttonBox_clicked(QAbstractButton*)
{
	qWarning("TODO: %s	%d",__FILE__,__LINE__);
}
