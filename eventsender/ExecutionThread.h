#ifndef EXECUTIONTHREAD_H
#define EXECUTIONTHREAD_H

#include <QThread>

/// Used to execute 
class ExecutionThread : public QThread
{
    Q_OBJECT

public:
    ExecutionThread(QObject *parent);
    ~ExecutionThread();
    
    void usleep(unsigned int pause_msecs);
    virtual void run();

private:
    unsigned int m_pause;
};

#endif // EXECUTIONTHREAD_H
