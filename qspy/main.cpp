
#include <QApplication>
#include "qspyform.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QSpyForm  qSpyForm;
	qSpyForm.show();
	return app.exec();
}
