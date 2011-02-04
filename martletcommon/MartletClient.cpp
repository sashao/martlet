#include "MartletClient.h"
#include "xmlrpc/client.h"

#include <QMessageBox>
#include <QApplication>

MartletClient::MartletClient()
  : textId(-1)
  , m_connected(false)
{
    m_client.reset( new xmlrpc::Client(this) );
    
    connect( client(), SIGNAL(done( int, QVariant )),
             this, SLOT(processReturnValue( int, QVariant )) );
    connect( client(), SIGNAL(failed( int, int, QString )),
             this, SLOT(processFault( int, int, QString )) );
    
}

MartletClient::~MartletClient()
{

}

bool MartletClient::tryConnect()
{
    qDebug(Q_FUNC_INFO);
    if (!m_connected) { // client connects only once, hell with it - it is HTTP
        //m_connected = false;
        client()->setHost( "localhost", 7777 );
    }
    client()->request("ping");

    qDebug("MartletClient::tryConnect() Ceck if connected .. ");
    return isConnected();
}

bool MartletClient::isConnected()
{
    return m_connected;
}

void MartletClient::disconnect()
{
    m_connected = false;
}

xmlrpc::Client* MartletClient::client()
{
    return m_client.data();
}

void MartletClient::processReturnValue( int requestId, QVariant value )
{
    m_connected = true;
    qDebug()<< "Got responce from the server  " <<  value;
    qDebug()<< "textId == "<< textId << " | requestId == " << requestId;
    if(requestId == textId){
        emit recordedTextArrived(value.toString());
        textId = -1;
    } else {
    }
}

void MartletClient::processFault( int requestId, int errorCode, QString errorString )
{
    if (!m_connected) { // handle only after connected errors.
        return;
    }
    Q_UNUSED(requestId);
    QMessageBox::warning(0, tr("Request failed"),
         QString("XML-RPC request  failed.\n\nFault code: %1\n'%2'\n") \
         .arg(errorCode).arg(errorString),
         QMessageBox::Ok );
}

void MartletClient::uploadScript(const QString& relativePath, const QString& scriptLines)
{
    client()->request("playback::upload", relativePath, scriptLines );
}

void MartletClient::play(const QString& relativePath)
{
    client()->request("playback::play", relativePath );
}

     
void MartletClient::startRecording(QString fname)
{
    client()->request("recording::start", fname);
}

void MartletClient::stopRecording(QString fname)
{
    client()->request("recording::stop", fname);
}

void MartletClient::askForRecordedText(QString fname)
{
    Q_ASSERT(textId == -1);
    textId = client()->request("recording::get", fname);
    Q_ASSERT(textId != -1);
}

void MartletClient::startSpy()
{
    client()->request("spy::start");
}

void MartletClient::stopSpy()
{
    client()->request("spy::stop");    
}


