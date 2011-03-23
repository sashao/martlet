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





