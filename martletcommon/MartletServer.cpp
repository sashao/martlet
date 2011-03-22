#include "MartletServer.h"
#include "RequestToRemote.h"
#include "AbstractEventFabric.h"

#include <QMessageBox>
#include <QApplication>



MartletServer::MartletServer(void (*spy)(QObject*))
    : m_server(new QRemoter(this))
    , m_catcher(this)
{
    m_catcher.m_spy = spy;
    //register sum and difference methods, with return type int and two int parameters
    connect( m_server.data(), SIGNAL(connected()),
             this, SLOT(connected()));
    connect( m_server.data(), SIGNAL(disconnected()),
             this, SLOT(disconnected()));

    const short port = 2877;

    bool r;
    r = m_server->connectRemoteSignal(SPY_START_0, this, SLOT(startSpy()));
    Q_ASSERT( r );
    r = m_server->connectRemoteSignal(SPY_STOP_0, this, SLOT(stopSpy()));
    Q_ASSERT( r );

    r = m_server->connectRemoteSignal(RECORDING_START_1, this, SLOT(record(QVariant)));
    Q_ASSERT( r );
    r = m_server->connectRemoteSignal(RECORDING_STOP_1, this, SLOT(stopRecording(QVariant)));
    Q_ASSERT( r );
    r = m_server->connectRemoteSignal(RECORDING_GET_1, this, SLOT(getRecordedText(QVariant)));
    Q_ASSERT( r );

    r = m_server->connectRemoteSignal(PLAYBACK_UPLOAD_2,
                                   this, SLOT(uploadScript(QVariant, QVariant)));
    Q_ASSERT( r );
    r = m_server->connectRemoteSignal(PLAYBACK_PLAY_1,
                                  this, SLOT(play(QVariant)));
    Q_ASSERT( r );
    r = m_server->connectRemoteSignal(PLAYBACK_STOP_0, this, SLOT(stopPlayback()));
    Q_ASSERT( r );
    r = m_server->connectRemoteSignal(APP_QUIT_0, this, SLOT(quit()));
    Q_ASSERT( r );

//    m_server->connectSignalToRemote()

    m_server->connectToHost( "127.0.0.1", port );
}

QRemoter *MartletServer::client()
{
    return m_server.data();
}

void MartletServer::connected()
{
//    QMessageBox::information(0, "Connected", "Connected \n\n\n\n\n\n");
    qDebug(Q_FUNC_INFO);
}

void MartletServer::disconnected()
{
//    QMessageBox::information(0, "DDDDD", "DISCONNECT \n\n\n\n\n\n");
    QApplication::quit();
//    qDebug(Q_FUNC_INFO);
}

void MartletServer::startSpy()
{
    qDebug(Q_FUNC_INFO);
}

void MartletServer::stopSpy()
{
    qDebug(Q_FUNC_INFO);
}

void MartletServer::quit()
{
    QApplication::exit(0);
}

void MartletServer::uploadScript(const QVariant& relativePath, const QVariant& scriptLines)
{
    m_filesystem.insert(relativePath.toString(), scriptLines.toString());
//    QMessageBox::information(0, "MartletServer::uploadScript", scriptLines.toString());
}

void MartletServer::play(const QVariant& relativePath)
{
//    QMessageBox::information(0, "MartletServer::play", relativePath.toString());
    if (m_filesystem.contains(relativePath.toString())) {
        m_catcher.blockSpontaneousEvents(true);
        m_server->connectSignalToRemote(AbstractEventFabric::instance(),
                                        SIGNAL(startingTest(QVariant)),
                                        PLAYBACK_TEST_START_1);
        m_server->connectSignalToRemote(AbstractEventFabric::instance(),
                                        SIGNAL(testFinished(QVariant,QVariant)),
                                        PLAYBACK_TEST_DONE_2);
        AbstractEventFabric::instance()->playAll(m_filesystem.value(relativePath.toString()));
        AbstractEventFabric::instance()->disconnect(0, 0, 0);
        m_catcher.blockSpontaneousEvents(false);
        m_server->perform(PLAYBACK_FINISHED_0);
    }
}

void MartletServer::stopPlayback()
{
    qDebug(Q_FUNC_INFO);
}

void MartletServer::record(const QVariant& /*suiteName*/)
{
    qDebug(Q_FUNC_INFO);
    m_catcher.startRecording();
}

void MartletServer::stopRecording(const QVariant& /*suiteName*/)
{
    qDebug(Q_FUNC_INFO);
    m_catcher.stopRecording();
}

void MartletServer::getRecordedText(const QVariant& /*suiteName*/)
{
    qDebug(Q_FUNC_INFO);
    const QString ret = AbstractEventFabric::instance()->getOutput();
    m_server->perform(RECORDING_OUTPUT_1, ret);
}



