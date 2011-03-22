#include <QtGui/QApplication>
#include "MartletWindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(main);
    QApplication a(argc, argv);
    MartletWindow w;
    w.show();
    return a.exec();
}
