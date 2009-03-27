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
