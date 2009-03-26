
#include <QCoreApplication>
#include <QEvent>

#include "filter.h"

static bool installed = false;
/*
int QCoreApplication::exec()
{
    printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");


}

void QCoreApplication::exit(int)
{
    printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}
*/

bool QCoreApplication::event(QEvent *e)
{
//	printf(":)  %d \n", e->type());
    if (e->type() == QEvent::Quit) {
        quit();
        return true;
    }

	if (e->type() == QEvent::ApplicationActivate && !installed)
	{

		QCoreApplication::instance()->installEventFilter( new filter());
		installed = true;
	}
	return QObject::event(e);
}


