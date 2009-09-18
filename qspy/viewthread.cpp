/*#include "viewthread.h"
#include <QtDebug>


ViewThread::ViewThread()
{
    spyDialog = new SpyDialog;
    spyDialog->setModal(false);
}

void ViewThread::run()
{
    spyDialog->show();
    exec();
}

void ViewThread::setNewData(QObject* obj)
{
    qDebug() << obj->metaObject()->className();
    spyDialog->updateData(obj);
}
*/
