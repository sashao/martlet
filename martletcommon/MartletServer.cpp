#include "MartletServer.h"
#include "RequestToRemote.h"
#include "AbstractEventFabric.h"



MartletServer::MartletServer():
        m_catcher(this)
{
    m_server.reset( new QRemoter(this) );

    //register sum and difference methods, with return type int and two int parameters
//    server->registerMethod( "ping", QVariant::Int );

//    server->registerMethod( "spy::start", QVariant::Int );
//    server->registerMethod( "spy::stop" , QVariant::Int);

//    server->registerMethod( "recording::start", QVariant::Int, QVariant::String );
//    server->registerMethod( "recording::stop" , QVariant::Int, QVariant::String);
//    server->registerMethod( "recording::get"  , QVariant::String, QVariant::String);
    
//    server->registerMethod( "playback::upload" , QVariant::Int, QVariant::String, QVariant::String);
//    server->registerMethod( "playback::play"   , QVariant::Int, QVariant::String);
    
//    connect( server, SIGNAL(incomingRequest( int, QString, QList<xmlrpc::Variant>)),
//             this, SLOT(processRequest( int, QString, QList<xmlrpc::Variant>)));
    
    const short port = 2877;
    m_server->connectToHost( "127.0.0.1", port );

//        qDebug() << "Listening for XML-RPC requests on port" << port;
//    } else {
//        qDebug() << "Error listening port" << port;
//    }
}

//void MartletServer::processRequest( int requestId, QString methodName, QList<xmlrpc::Variant> parameters )
//{
//    // we doun't have to check parameters count and types here
//    // since we registered methods "sum" and "difference"
//    // with server->registerMethod() call

////    int x = parameters[0].toInt();
////    int y = parameters[1].toInt();

//    qDebug() << methodName <<  "   params == " << parameters;// << x << y;

//    if ( methodName == QString("recording::start") ) {
//        record(parameters[0].toString());
//        server->sendReturnValue( requestId, 0 );
//    } else if ( methodName == "recording::stop" ) {
//        stopRecording(parameters[0].toString());
//        server->sendReturnValue( requestId, 0 );
//    } else if ( methodName == "recording::get" ) {
//        qDebug("about to get text");
//        const QString result  = getRecordedText(parameters[0].toString());
//        qDebug() << "SZ "<< result.size();
//        //qDebug() << "\n\n\n\\n\n\n  We recorded :" <<  result << "\n\n\n\n\n\n";
//        server->sendReturnValue( requestId, result);
//    } else if ( methodName == "ping" ) {
//        server->sendReturnValue( requestId, "pong" );
//    } else if ( methodName == "spy::start" ) {
//        // TODO
//        server->sendReturnValue( requestId, 0 );
//    } else if ( methodName == "spy::stop" ) {
//        // TODO
//        server->sendReturnValue( requestId, 0 );
//    } else if ( methodName == "playback::upload" ) {
//        server->sendReturnValue( requestId, uploadScript(parameters[0].toString(), parameters[1].toString()));
//    } else if ( methodName == "playback::play" ) {
//        QString path = parameters[0].toString();
//        server->sendReturnValue( requestId, play(path));
//    } else {
//        qDebug() << " Unhandled request "<< methodName;
//    }
//}

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

int MartletServer::record(const QString& suiteName)
{
    m_catcher.startRecording();
    return 0;
}

int MartletServer::stopRecording(const QString& suiteName)
{
    m_catcher.stopRecording();
    return 0;
}

QString MartletServer::getRecordedText(const QString suiteName)
{
    // TODO
    return AbstractEventFabric::instance()->getOutput();
}



