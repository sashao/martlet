#include <QtGui/QApplication>
#include "MartletWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MartletWindow w;
    w.show();
    return a.exec();
}
