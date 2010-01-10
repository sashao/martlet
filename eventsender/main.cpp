#include <QtGui/QApplication>
#include "eventsender.h"

#include "AbstractEventFabric.h"
#include "CSVEventFabric.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	AbstractEventFabric::setInstance(new CSVEventFabric(0));

	eventsender w;
	w.show();
	return a.exec();
}
