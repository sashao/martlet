#include "MartletClient.h"
#include "xmlrpc/client.h"

#include <QMessageBox>

MartletClient::MartletClient()
{
//    requestIdSum = -1;
//    requestIdDiff = -1;

    m_client = new xmlrpc::Client(this);
    
    connect( client(), SIGNAL(done( int, QVariant )),
             this, SLOT(processReturnValue( int, QVariant )) );
    connect( client(), SIGNAL(failed( int, int, QString )),
             this, SLOT(processFault( int, int, QString )) );
    
    client()->setHost( "localhost", 7777 );
}

MartletClient::~MartletClient()
{
    delete m_client;
}


xmlrpc::Client* MartletClient::client()
{
    return m_client;
}

void MartletClient::processReturnValue( int requestId, QVariant value )
{
    //client();
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

     
void MartletClient::startRecording()
{
    client()->request("recording::start");
}

void MartletClient::stopRecording()
{
    client()->request("recording::stop");
}

QString MartletClient::getRecorded()
{
    //client()->
}


