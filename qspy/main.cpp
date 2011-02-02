
#include <QApplication>
#include <QDebug>
#include <QProcess>
#include "qspyform.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

    qDebug() << QProcess::systemEnvironment();

	QSpyForm  qSpyForm;
	qSpyForm.show();
	return app.exec();
}
