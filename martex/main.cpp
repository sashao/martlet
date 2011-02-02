#include <QtGui/QApplication>

#include <stdio.h>
#include <stdlib.h>
#include <QInjector.h>
#include <QFile>
#include <QDebug>

#ifdef Q_OS_WIN
#include <windows.h>
#else
#include <dlfcn.h>
#endif

int main(int argc, char *argv[])
{
	qWarning("TODO: %s:%d", __FILE__, __LINE__);
    QApplication a(argc, argv);
    if (argc != 2) {
        qDebug("Usage: martex <qt executable>");
        return -1;
    }
	QString str(QObject::tr("translate me"));

#ifdef Q_OS_WIN

        const QString appName(argv[1]);
		QInjector inj;
        if (!inj.libraryFileExists()) {
            qDebug()<<"Injection library does not exist. Ecpected "<< inj.libraryPath();
        } else if (QFile::exists(appName)) {
            qDebug()<<"Injection library : "<< inj.libraryPath();
            qDebug()<<"Application : "<< appName;            
            inj.start(appName);
        } else {
            qDebug()<<"Application does not exist. Given "<< appName;            
        }

#else
                    QInjector inj;
                    inj.start(argv[1]);
//		    int ret;
//            char *nargv[] = { (char *)0 };
//            char *env[] = { "HOME=/home/oomel", "LOGNAME=oomel", "DISPLAY=:0.0", "LD_PRELOAD=./libQtLoad.so", (char *)0 };
//            ret = execve (argv[1], nargv, env);


#endif
			return a.exec();
        return 0;
}





