#include "qspyform.h"

#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>


QSpyForm::QSpyForm( QWidget * parent, Qt::WindowFlags f) : QWidget(parent,f)
{
	setupUi(this);
	martexProc = 0;
	messageLabel->setVisible(false);
	startStopPushButton->setText(tr("Start"));
#ifdef Q_OS_WIN
	martexPath = QString("../bin/martex.exe");
#else
	martexPath = QString("../bin/martex");
#endif
	this->setMinimumWidth(250);
	settings = new QSettings("oomel&akyryl", "qspy");
	settings->sync();

	// load combo items
	QStringList comboItems = settings->value("PathComboItems").toString().split(",");
	foreach (QString item, comboItems)
		appPathComboBox->addItem(item);
}

QSpyForm::~QSpyForm()
{
	if (martexProc && martexProc->state() == QProcess::Running) {
		martexProc->terminate();
		martexProc->waitForFinished(3000);
	}
	// save combo items
	QString comboItems = QString("");
	for (int i = 0; i < appPathComboBox->count(); ++i)
	{
		comboItems += appPathComboBox->itemText(i);
		if (i != appPathComboBox->count() - 1)
			comboItems += QString(",");
	}
	settings->setValue("PathComboItems", comboItems);
	settings->sync();
}

void QSpyForm::on_spyGroup_toggled(bool)
{
	qWarning("TODO: %s	%d",__FILE__,__LINE__);
}

void QSpyForm::on_appPathComboBox_activated(const QString&)
{
	qWarning("TODO: %s	%d",__FILE__,__LINE__);
}

void QSpyForm::on_dirToolButton_clicked()
{
	QString appPath;
#ifdef Q_OS_WIN
	appPath = QFileDialog::getOpenFileName(this,
		tr("Open Application"), "", tr("Execute Files (*.exe)"));
#else
	appPath = QFileDialog::getOpenFileName(this,
		tr("Open Application"), "", tr("Execute Files (*)"));
#endif
	if (!appPath.isEmpty())
		appPathComboBox->setEditText(appPath);
}

void QSpyForm::on_startStopPushButton_clicked()
{
	if (startStopPushButton->text() == QString(tr("Start")))
		startProcess();
	else
		stopProcess();
}

bool QSpyForm::startProcess()
{
	QString appPath = appPathComboBox->currentText();
	if (QFile::exists(appPath))
	{
		if (!martexProc)
			martexProc = new QProcess();
		if (martexProc->state() == QProcess::Running)
		{
			setStopState(tr("Process already running.") + appPath);
			return false;
		}
		martexProc->start(martexPath, QStringList() << appPath);
		if (!martexProc->waitForStarted())
		{
			setStopState(tr("Unable to start ") + appPath);
			return false;
		}
		setRunningState(tr("Running..."), appPath);
	}
	else
	{
		setStopState(tr("App path is incorrect!"), true, appPath);
		return false;
	}
	return true;
}

bool QSpyForm::stopProcess()
{
	if (martexProc && martexProc->state() == QProcess::Running) {
		martexProc->terminate();
		martexProc->waitForFinished(3000);
		setStopState("", false);
		return true;
	}
	return false;
}

void QSpyForm::setRunningState(QString message, QString appPath)
{
	startStopPushButton->setText(tr("Stop"));
	messageLabel->setVisible(true);
	messageLabel->setText(message);
	if (appPathComboBox->findText(appPath) == -1)
		appPathComboBox->addItem(appPath);
	appPathComboBox->setEnabled(false);
	dirToolButton->setEnabled(false);
}

void QSpyForm::setStopState(QString message, bool isMsgLabelVisible, QString appPath)
{
	messageLabel->setVisible(isMsgLabelVisible);
	messageLabel->setText(message);
	startStopPushButton->setText(("Start"));
	appPathComboBox->setEnabled(true);
	dirToolButton->setEnabled(true);
	// if path passes to this function only if it is incorrect, so remove them from settings
	if (appPathComboBox->findText(appPath) != -1)
	{
		// remove incorrect path
		appPathComboBox->removeItem(appPathComboBox->findText(appPath));
		// but leave it in edit
		appPathComboBox->setEditText(appPath);
	}
}
