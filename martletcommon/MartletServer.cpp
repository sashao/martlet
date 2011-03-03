#include "MartletServer.h"
#include "RequestToRemote.h"
#include "AbstractEventFabric.h"

#include <QMessageBox>



MartletServer::MartletServer()
    : m_server(new QRemoter(this))
    , m_catcher(this)
{
    //register sum and difference methods, with return type int and two int parameters
    connect( m_server.data(), SIGNAL(connected()),
             this, SLOT(connected()));
    connect( m_server.data(), SIGNAL(disconnected()),
             this, SLOT(disconnected()));

    const short port = 2877;

    m_server->connectRemoteSignal(SPY_START_0, this, SLOT(startSpy()), 1);
    m_server->connectRemoteSignal(SPY_STOP_0, this, SLOT(stopSpy()), 1);

    m_server->connectRemoteSignal(RECORDING_START_1, this, SLOT(record(QVariant)), 1);
    m_server->connectRemoteSignal(RECORDING_STOP_1, this, SLOT(stopRecording(QVariant)), 1);
    m_server->connectRemoteSignal(RECORDING_GET_1, this, SLOT(getRecordedText(QVariant)), 1);

    m_server->connectRemoteSignal(PLAYBACK_UPLOAD_2,
                                   this, SLOT(uploadScript(QVariant, QVariant)), 2);
    m_server->connectRemoteSignal(PLAYBACK_PLAY_1,
                                  this, SLOT(play(QVariant)), 1);
    m_server->connectRemoteSignal(PLAYBACK_STOP_0, this, SLOT(stopPlayback()), 1);

    m_server->connectToHost( "127.0.0.1", port );
}

void MartletServer::connected()
{
//    QMessageBox::information(0, "Connected", "Connected \n\n\n\n\n\n");
    qDebug(Q_FUNC_INFO);
}

void MartletServer::disconnected()
{
//    QMessageBox::information(0, "DDDDD", "DISCONNECT \n\n\n\n\n\n");
    qDebug(Q_FUNC_INFO);
}

void MartletServer::startSpy()
{
    qDebug(Q_FUNC_INFO);
}

void MartletServer::stopSpy()
{
    qDebug(Q_FUNC_INFO);
}

void MartletServer::uploadScript(const QVariant& relativePath, const QVariant& scriptLines)
{
    m_filesystem.insert(relativePath.toString(), scriptLines.toString());
//    QMessageBox::information(0, "MartletServer::uploadScript", scriptLines.toString());
}

void MartletServer::play(const QVariant& relativePath)
{
//    QMessageBox::information(0, "MartletServer::play", relativePath.toString());
    if (m_filesystem.contains(relativePath.toString()))
    AbstractEventFabric::instance()->playAll(m_filesystem.value(relativePath.toString()));
}

void MartletServer::stopPlayback()
{
    qDebug(Q_FUNC_INFO);
}

void MartletServer::record(const QVariant& /*suiteName*/)
{
    m_catcher.startRecording();
}

void MartletServer::stopRecording(const QVariant& /*suiteName*/)
{
    m_catcher.stopRecording();
}

void MartletServer::getRecordedText(const QVariant /*suiteName*/)
{
    const QString ret = AbstractEventFabric::instance()->getOutput();
    m_server->perform(RECORDING_OUTPUT_1, ret);
}



