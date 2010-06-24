#include "MartletClient.h"
#include "xmlrpc/client.h"

#include <QMessageBox>

MartletClient::MartletClient() :
        textId(-1)
{
//    requestIdSum = -1;
//    requestIdDiff = -1;

    m_client = new xmlrpc::Client(this);
    
    connect( client(), SIGNAL(done( int, QVariant )),
             this, SLOT(processReturnValue( int, QVariant )) );
    connect( client(), SIGNAL(failed( int, int, QString )),
             this, SLOT(processFault( int, int, QString )) );
    
}

MartletClient::~MartletClient()
{
    delete m_client;
}

bool MartletClient::tryConnect()
{
     client()->setHost( "localhost", 7777 );
}

bool MartletClient::isConnected()
{
    // TODO
    return true;
}


xmlrpc::Client* MartletClient::client()
{
    return m_client;
}

void MartletClient::processReturnValue( int requestId, QVariant value )
{
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
    QMessageBox::warning(0, tr("Request failed"),
         QString("XML-RPC request  failed.\n\nFault code: %1\n'%2'\n") \
         .arg(errorCode).arg(errorString),
         QMessageBox::Ok );
}

void MartletClient::startApp(const QString& path, const QString& parameters)
{
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
    textId = client()->request("recording::get", fname);
}

void MartletClient::startSpy()
{
    client()->request("spy::start");
}

void MartletClient::stopSpy()
{
    client()->request("spy::stop");    
}


