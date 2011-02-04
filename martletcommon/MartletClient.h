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
    
    bool tryConnect();
    void disconnect();
    bool isConnected();

public:
     void uploadScript(const QString& relativePath, const QString& scriptLines);
     void play(const QString& relativePath);
     
     void startRecording(QString fname);
     void stopRecording(QString fname);
     // TODO: temporary thing. Remove this.
     void askForRecordedText(QString fname);
     
     // SPY
     void startSpy();
     void stopSpy();
    
signals:
    void aplicationStarted(int portID);
    void recordedTextArrived(QString text);

protected:
    xmlrpc::Client* client();

private slots:
    void processReturnValue( int requestId, QVariant value );
    void processFault( int requestId, int errorCode, QString errorString );

private:
    /// Communicates with remote app
    QScopedPointer<xmlrpc::Client> m_client;
    /// Comunicates with daemon, starts app
    QScopedPointer<xmlrpc::Client> m_appClient;
    
    int textId;
    bool m_connected;

};

#endif // MARTLETCLIENT_H
