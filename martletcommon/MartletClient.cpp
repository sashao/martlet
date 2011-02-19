#include "MartletClient.h"
#include "qnetworkrpc/src/QRemoter.h"
#include "RequestToRemote.h"

#include <QMessageBox>
#include <QApplication>

MartletClient::MartletClient()
  : textId(-1)
{
    m_client.reset( new QRemoter(this) );
    
//    connect( client(), SIGNAL(done( int, QVariant )),
//             this, SLOT(processReturnValue( int, QVariant )) );
//    connect( client(), SIGNAL(failed( int, int, QString )),
//             this, SLOT(processFault( int, int, QString )) );
    
}

MartletClient::~MartletClient()
{

}

bool MartletClient::tryConnect()
{
    qDebug(Q_FUNC_INFO);
    if (!client()->isConnected()) {
        client()->listen( 2877 );
    }

    qDebug("MartletClient::tryConnect() Ceck if connected .. ");
    return isConnected();
}

bool MartletClient::isConnected()
{
    return client()->isConnected();
}

//void MartletClient::disconnect()
//{
//    client()->;
//}

QRemoter* MartletClient::client()
{
    return m_client.data();
}

//void MartletClient::processReturnValue( int requestId, QVariant value )
//{
//    qDebug()<< "Got responce from the server  " <<  value;
//    qDebug()<< "textId == "<< textId << " | requestId == " << requestId;
//    if(requestId == textId){
//        emit recordedTextArrived(value.toString());
//        textId = -1;
//    } else {
//    }
//}

//void MartletClient::processFault( int requestId, int errorCode, QString errorString )
//{
//    if (!isConnected()) { // handle only after connected errors.
//        return;
//    }
//    Q_UNUSED(requestId);
//    QMessageBox::warning(0, tr("Request failed"),
//         QString("XML-RPC request  failed.\n\nFault code: %1\n'%2'\n") \
//         .arg(errorCode).arg(errorString),
//         QMessageBox::Ok );
//}

void MartletClient::uploadScript(const QString& relativePath, const QString& scriptLines)
{
    client()->perform(PLAYBACK_UPLOAD, relativePath, scriptLines);
}

void MartletClient::play(const QString& relativePath)
{
    client()->perform(PLAYBACK_PLAY, relativePath );
}

     
void MartletClient::startRecording(QString fname)
{
    client()->perform(RECORDING_START, fname);
}

void MartletClient::stopRecording(QString fname)
{
    client()->perform(RECORDING_STOP, fname);
}

void MartletClient::askForRecordedText(QString fname)
{
    client()->perform(RECORDING_GET, fname);
}

void MartletClient::startSpy()
{
    client()->perform(SPY_START);
}

void MartletClient::stopSpy()
{
    client()->perform(SPY_STOP);
}


