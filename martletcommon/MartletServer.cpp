#include "MartletServer.h"
#include "xmlrpc/server.h"
#include "AbstractEventFabric.h"


MartletServer::MartletServer():
        m_catcher(this)
{
    server = new xmlrpc::Server(this);

    //register sum and difference methods, with return type int and two int parameters
    server->registerMethod( "recording::start", QVariant::Int );
    server->registerMethod( "recording::stop" , QVariant::Int);
    
    server->registerMethod( "playback::upload" , QVariant::Int, QVariant::String, QVariant::String);
    server->registerMethod( "playback::play"   , QVariant::Int, QVariant::String);
    
    connect( server, SIGNAL(incomingRequest( int, QString, QList<xmlrpc::Variant>)),
             this, SLOT(processRequest( int, QString, QList<xmlrpc::Variant>)));
    
    const short port = 7777;
    if( server->listen( port ) ) {
        qDebug() << "Listening for XML-RPC requests on port" << port;
    } else {
        qDebug() << "Error listening port" << port;
    }
}

void MartletServer::processRequest( int requestId, QString methodName, QList<xmlrpc::Variant> parameters )
{
    // we doun't have to check parameters count and types here
    // since we registered methods "sum" and "difference"
    // with server->registerMethod() call

//    int x = parameters[0].toInt();
//    int y = parameters[1].toInt();

    qDebug() << methodName <<  "   params == " << parameters;// << x << y; 

    if ( methodName == QString("recording::start") ) {
        qDebug() << methodName <<  "   params: " << parameters;// << x << y; 
        m_catcher.startRecording();
        server->sendReturnValue( requestId, 0 );
    } else if ( methodName == "recording::stop" ) {
        m_catcher.stopRecording();
        server->sendReturnValue( requestId, 0 ); 
    } else if ( methodName == "playback::upload" ) {
        server->sendReturnValue( requestId, uploadScript(parameters[0].toString(), parameters[1].toString()));
    } else if ( methodName == "playback::play" ) {
        QString path = parameters[0].toString();
        server->sendReturnValue( requestId, play(path));
    } else {
        qDebug() << " Unhandled request "<< methodName;
    }
}

int MartletServer::uploadScript(const QString& relativePath, const QString& scriptLines)
{
    m_filesystem.insert(relativePath, scriptLines);
    return 0;
}

int MartletServer::play(const QString& relativePath)
{
    AbstractEventFabric::instance()->playAll(m_filesystem.value(relativePath));
    return 0;
}




