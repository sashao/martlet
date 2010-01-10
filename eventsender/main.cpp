#include <QtGui/QApplication>
#include "eventsender.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	eventsender w;
	w.show();
	return a.exec();
}
