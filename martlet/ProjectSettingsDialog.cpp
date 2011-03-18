/* @COPYRIGHT@ */

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
