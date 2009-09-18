#include <QtGui/QApplication>

#include <stdio.h>
#include <stdlib.h>

#ifdef Q_OS_WIN


#include <QProcess>
#include <QObject>
#include <QThread>
#include <QDebug>

#include <windows.h>
#include <QInjector.h>



#else

#include <dlfcn.h>

#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	if (argc < 1) return -1;
	QString str(QObject::tr("translate me"));
	qWarning("TODO check for lib existance: %s:%d", __FILE__, __LINE__);
	qWarning("TODO check for executable existance: %s:%d", __FILE__, __LINE__);
	qWarning("TODO: %s:%d", __FILE__, __LINE__);

#ifdef Q_OS_WIN

		QInjector inj;
		QString name(argv[1]/*"loopback.exe"*/);
		inj.start(name);

//QThread::currentThread()->wait(2000);  


#else
		    int ret;
            char *nargv[] = { (char *)0 };
            char *env[] = { "HOME=/home/oomel", "LOGNAME=oomel", "DISPLAY=:0.0", "LD_PRELOAD=./libQtLoad.so", (char *)0 };
            ret = execve (argv[1], nargv, env);

#endif
			return a.exec();
}





