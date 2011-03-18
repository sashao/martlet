/* @COPYRIGHT@ */

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
