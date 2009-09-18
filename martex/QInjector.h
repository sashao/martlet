#pragma once

#include <QObject>
#include <QProcess>

class QInjector :
	public QObject
{
	Q_OBJECT
public:
	QInjector(void);
	~QInjector(void);
	void QInjector::start(QString name);
protected:
	QProcess * proc;
protected slots:
	void inject();
	void on_proc_started();
	void on_proc_stateChanged ( QProcess::ProcessState newState );
	void on_proc_finished ( int exitCode, QProcess::ExitStatus exitStatus );

};

