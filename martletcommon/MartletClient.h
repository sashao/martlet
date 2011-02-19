#ifndef MARTLETCLIENT_H
#define MARTLETCLIENT_H

#include <QObject>
#include <QVariant>

class QRemoter;
        
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
    bool isConnected();
    QRemoter* client();

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

private slots:
//    void processReturnValue( int requestId, QVariant value );
//    void processFault( int requestId, int errorCode, QString errorString );

private:
    /// Communicates with remote app
    QScopedPointer<QRemoter> m_client;
    /// Comunicates with daemon, starts app
    QScopedPointer<QRemoter> m_appClient;
    
    int textId;
};

#endif // MARTLETCLIENT_H
