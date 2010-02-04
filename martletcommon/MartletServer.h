#ifndef MARTLETSERVER_H
#define MARTLETSERVER_H

#include <QObject>
#include <QMap>
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
    int uploadScript(const QString& relativePath, const QString& scriptLines);
    int play(const QString& relativePath);

private:
    xmlrpc::Server *server;
    EventCatcher m_catcher;
    QMap<QString, QString> m_filesystem;
};

#endif // MARTLETSERVER_H
