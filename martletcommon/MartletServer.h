#ifndef MARTLETSERVER_H
#define MARTLETSERVER_H

#include <QObject>
#include "xmlrpc/variant.h"
#include "EventCatcher.h"

namespace xmlrpc {
    class Server;
}

class MartletServer : public QObject
{
    Q_OBJECT
public:
    MartletServer();

private slots:
    void processRequest( int requestId, QString methodName, QList<xmlrpc::Variant> parameters );

private:
    xmlrpc::Server *server;
    EventCatcher m_catcher;
};

#endif // MARTLETSERVER_H
