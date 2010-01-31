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
    client();
}

void MartletClient::processFault( int requestId, int errorCode, QString errorString )
{
    QMessageBox::critical(0, "Error", errorString, QMessageBox::Ok);
}

