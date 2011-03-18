#ifndef MARTLETSERVER_H
#define MARTLETSERVER_H

#include <QObject>
#include <QMap>
#include <QVariant>
#include "EventCatcher.h"
#include "qnetworkrpc/src/QRemoter.h"

/**
  * Execute comands on testable app.
  */
class MartletServer : public QObject
{
    Q_OBJECT
public:
    MartletServer( void (*spy)(QObject*) );
    QRemoter *client();

private slots:
    void connected();
    void disconnected();

    void uploadScript(const QVariant& relativePath, const QVariant& scriptLines);
    void play(const QVariant& relativePath);
    void stopPlayback();

    void startSpy();
    void stopSpy();

    void quit();

    //     RECORDING RELATED
    void record(const QVariant& suiteName);
    void stopRecording(const QVariant& suiteName);
    void getRecordedText(const QVariant& suiteName);

private:
    QScopedPointer<QRemoter> m_server;
    EventCatcher m_catcher;
    QMap<QString, QString> m_filesystem;
};

#endif // MARTLETSERVER_H
