#ifndef MARTLETCLIENT_H
#define MARTLETCLIENT_H

#include <QObject>
#include <QVariant>

namespace xmlrpc {
    class Client;
}
        
class MartletClient : public QObject
{
    Q_OBJECT
public:
    enum ClientMode {
        None,
        StartingApp,
        RunningScript
    };
    
    MartletClient();
    ~MartletClient();

public:
     void startApp(const QString& path, const QString& parameters);
     void uploadScript(const QString& relativePath, const QString& scriptLines);
     void paly(const QString& relativePath);
     
     void startRecording();
     void stopRecording();
     // TODO: temporary thing. Remove this.
     QString getRecorded();
    
signals:
    void aplicationStarted(int portID);

protected:
    xmlrpc::Client* client();
private slots:
    void processReturnValue( int requestId, QVariant value );
    void processFault( int requestId, int errorCode, QString errorString );

private:
    /// Communicates with remote app
    xmlrpc::Client *m_client;
    /// Comunicates with daemon, starts app
    xmlrpc::Client *m_appClient;    

};

#endif // MARTLETCLIENT_H
