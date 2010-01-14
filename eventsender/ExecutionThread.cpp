#include "ExecutionThread.h"

ExecutionThread::ExecutionThread(QObject *parent)
    : QThread(parent)
    , m_pause(0)
{

}

ExecutionThread::~ExecutionThread()
{

}

void ExecutionThread::usleep(unsigned int pause_msecs)
{
    //wait(pause_msecs);
    msleep(pause_msecs);
}

void ExecutionThread::run()
{
    //exec();
}
