#include <QtGui/QApplication>
#include "CutterMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CutterMainWindow w;
    w.show();
    return a.exec();
}
