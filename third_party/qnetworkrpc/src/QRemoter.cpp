/*
Copyright (C) 2011 Oleksandr Omelchuk

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
more details. You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "QRemoter.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QRegExp>
#include "QRemoterSignalsWatcer.h"
#include "QStringProtocol.h"

const int QRemoter::m_sizeFieldSize = 6;
const int QRemoter::m_sizeFieldBase = 36;

//#define Q_ASSERT(...)

QRemoter::QRemoter(QObject *parent)
    : QObject(parent)
    , m_tcpServer(new QTcpServer(this))
    , m_tcpClient(new QTcpSocket(this))
    , m_tcpConnection(0)
    , m_gotCommandSize(-1)
    , m_protocol(new QStringProtocol(this))
{
    connect(m_tcpServer, SIGNAL(newConnection()),
                 this, SLOT(acceptConnection()));

    connect(m_tcpClient, SIGNAL(connected()),
            this, SLOT(clientConnected()));
    connect(m_tcpClient, SIGNAL(readyRead()),
                 this, SLOT(onReadyRead()));
    connect(m_tcpClient, SIGNAL(disconnected()),
            this, SLOT(clientDisconnected()));
    connect(m_tcpClient, SIGNAL(hostFound()),
            this, SLOT(onClientHostFound()));
    connect(m_tcpClient, SIGNAL(bytesWritten(qint64)),
                 this, SLOT(updateClientProgress(qint64)));
    connect(m_tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
                 this, SLOT(displayError(QAbstractSocket::SocketError)));

    m_tcpClient->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    m_tcpClient->setSocketOption(QAbstractSocket::LowDelayOption, 1);
}

QRemoter::~QRemoter()
{
    if (isConnected()) {
        m_tcpConnection->disconnectFromHost();
        if ( m_tcpConnection ) {
            m_tcpConnection->waitForDisconnected();
        }
    }
}

void QRemoter::listen(quint16 port)
{
    Q_ASSERT(m_tcpConnection == 0);
    if (!m_tcpServer->isListening() && !m_tcpServer->listen(QHostAddress::Any, port)) {
/*             QMessageBox::StandardButton ret = QMessageBox::critical(0,
                                             tr("QRemoter"),
                                             tr("Unable to start listening: %1.")
                                             .arg(m_tcpServer->errorString()),
                                             QMessageBox::Retry
                                             | QMessageBox::Cancel);
             if (ret == QMessageBox::Cancel)
                 return;
*/
         }
    qDebug("QRemoter: %s Listening", qPrintable(objectName()));
}

void QRemoter::connectToHost ( const QString & hostName, quint16 port)
{
    qDebug("QRemoter: %s Connecting", qPrintable(objectName()));
    Q_ASSERT(m_tcpConnection == 0);
    m_tcpClient->connectToHost(hostName, port);
    m_tcpConnection = m_tcpClient;
}

void QRemoter::onClientHostFound ()
{
//    qDebug("QRemoter: %s onClientHostFound %d %d", qPrintable(objectName()), m_tcpConnection->localPort(), m_tcpConnection->peerPort());
}

bool QRemoter::isConnected()
{
    if (m_tcpConnection) {
        Q_ASSERT(m_tcpConnection->isOpen());
        Q_ASSERT(m_tcpConnection->isWritable());
        Q_ASSERT(m_tcpConnection->isReadable());

        return (m_tcpConnection->state() == QTcpSocket::ConnectedState);
    }
    return false;
}

void QRemoter::stopConnecting()
{
    if (m_tcpConnection != 0 ) {
        m_tcpConnection->abort();
    }
}

void QRemoter::setProtocol(QAbstractProtocol* newProtocol)
{
    Q_ASSERT(!isConnected());
    delete m_protocol;
    m_protocol = newProtocol;
    m_protocol->setParent(this);
}

int getParamsCount(const char * method)
{
   const QString m = method;
   if (m.contains(',')) {
        return m.count(',') + 1;
   } else {
       static const QRegExp emptyBraces("\\(\\s*\\)");
       if (emptyBraces.indexIn(m) >= 0) {
           return 0;
       } else {
           return 1;
       }
   }
}

bool QRemoter::connectSignalToRemote(const QObject * sender,
                                     const char * signal,
                                     const QString& commandName )
{
    Q_ASSERT(sender != 0);
    Q_ASSERT(signal != 0);
    Q_ASSERT(!commandName.isEmpty());
    const int paramsCount = getParamsCount(signal);
    QRemoterSignalsWatcer * watcher = 0;
    if (!m_connectionsMap.contains(commandName)) {
        watcher = new QRemoterSignalsWatcer(this, commandName, paramsCount);
        m_connectionsMap.insert(commandName, watcher);
    } else {
        watcher = m_connectionsMap.value(commandName);
        Q_ASSERT(watcher->paramsCount() == paramsCount);
    }
    Q_ASSERT(watcher != 0);
    const char* slot = SLOT(sendCommand());
    switch (paramsCount){
    case 1:
        slot = SLOT(sendCommand1(QVariant));
        break;
    case 2:
        slot = SLOT(sendCommand2(QVariant, QVariant));
        break;
    case 3:
        slot = SLOT(sendCommand3(QVariant, QVariant, QVariant));
        break;
    case 4:
    case 5:
        Q_ASSERT(!"NOT suported");
    }
    const bool result = connect( sender, signal, watcher, slot );
    if (!result) {
        qWarning("QRemoter: unable to connect signal");
    }
    Q_ASSERT(result);
    return result;
}

bool QRemoter::connectRemoteSignal(const QString& commandName,
                                   const QObject * receiver,
                                   const char * method  )
{
    Q_ASSERT(receiver != 0);
    Q_ASSERT(method != 0);
    Q_ASSERT(!commandName.isEmpty());
    const int paramsCount = getParamsCount(method);
    QRemoterSignalsWatcer * watcher = 0;
    if (!m_connectionsMap.contains(commandName)) {
        watcher = new QRemoterSignalsWatcer(this, commandName, paramsCount);
        m_connectionsMap.insert(commandName, watcher);
    } else {
        watcher = m_connectionsMap.value(commandName);
        Q_ASSERT(watcher->paramsCount() == paramsCount);
    }
    Q_ASSERT(watcher != 0);
    const char* signal = SIGNAL(gotResponce());
    switch (paramsCount){
    case 1:
        signal = SIGNAL(gotResponce1(QVariant));
        break;
    case 2:
        signal = SIGNAL(gotResponce2(QVariant, QVariant));
        break;
    case 3:
        signal = SIGNAL(gotResponce3(QVariant, QVariant, QVariant));
        break;
    case 4:
    case 5:
        Q_ASSERT(!"NOT suported");
    }

    const bool result = connect( watcher, signal,
                                 receiver, method );
    if (!result) {
        qWarning("QRemoter: unable to connect slot");
    }
    Q_ASSERT(result);
    return result;
}

void QRemoter::handleReceivedCommand(const QString& commandName,
                                     const QVariant& params )
{
    Q_ASSERT(m_connectionsMap.contains(commandName));
    QRemoterSignalsWatcer * watcher = m_connectionsMap.value(commandName);
    if (watcher) {
        watcher->notifyAboutResponce(params);
    }
}


void QRemoter::perform(const QString& name, const QVariant& params)
{
    if (isConnected()) {
//        qDebug("QRemoter: %s About to push command. %d %d", qPrintable(objectName()), m_tcpConnection->localPort(), m_tcpConnection->peerPort());
//        qDebug("%s Writing '%s'-'%s'", qPrintable(objectName()), qPrintable(name), qPrintable(params.toString()));

        QByteArray data;
        data.reserve(m_sizeFieldSize+140); // try to optimize
        for (int i=0; i<m_sizeFieldSize; ++i) {
            data.append( static_cast<char>(0)); // size of message
        }
        const QByteArray protodata = m_protocol->encodeValue(name, params);
        data.append(protodata); // actual data
        const QByteArray sz = QByteArray::number( static_cast<qlonglong>(data.size()), m_sizeFieldBase);
        Q_ASSERT(sz.size() <= m_sizeFieldSize);
        data.replace(m_sizeFieldSize-sz.size(), sz.size(), sz);
        // finally write it
        m_tcpConnection->write(data);
    }
}

void QRemoter::perform(const QString& name )
{
    perform(name, QVariant());
}

void QRemoter::perform(const QString& name, const QVariant& a1, const QVariant& a2)
{
    QVariantList vl;
    vl << a1 << a2;
    perform(name, vl);
}

void QRemoter::perform(const QString& name, const QVariant& a1, const QVariant& a2, const QVariant& a3)
{
    QVariantList vl;
    vl << a1 << a2 << a3;
    perform(name, vl);
}


void QRemoter::acceptConnection()
{
    m_tcpConnection = m_tcpServer->nextPendingConnection();
    m_tcpConnection->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    m_tcpConnection->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    Q_ASSERT(m_tcpConnection->isOpen());
    Q_ASSERT(m_tcpConnection->isWritable());
    Q_ASSERT(m_tcpConnection->isReadable());
    Q_ASSERT(m_tcpConnection->isValid());
    connect(m_tcpConnection, SIGNAL(readyRead()),
                 this, SLOT(onReadyRead()));
    connect(m_tcpConnection, SIGNAL(disconnected()),
            this, SLOT(clientDisconnected()));
    connect(m_tcpConnection, SIGNAL(error(QAbstractSocket::SocketError)),
                 this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(m_tcpConnection, SIGNAL(bytesWritten(qint64)),
                 this, SLOT(updateClientProgress(qint64)));

//    qDebug("QRemoter: %s Accepted connection", qPrintable(objectName()));

    emit connected();

    m_tcpServer->close();
}

void QRemoter::onReadyRead()
{
    Q_ASSERT(m_tcpConnection != 0);
    //qDebug() <<  objectName() <<  " Read " <<  m_tcpConnection->bytesAvailable() << 
    //      " bytes (m_gotCommandSize = " <<  m_gotCommandSize << ")";

    if (m_gotCommandSize > -1) {
        if ( m_tcpConnection->bytesAvailable() >= m_gotCommandSize ) {
            const QByteArray command = m_tcpConnection->read(m_gotCommandSize);
            const QPair <QString, QVariant> result = m_protocol->decodeString(command);

            m_gotCommandSize = -1;
            handleReceivedCommand(result.first, result.second);
        }
    } else {
        if ( m_tcpConnection->bytesAvailable() >= m_sizeFieldSize ) {
            QByteArray ba = m_tcpConnection->read(m_sizeFieldSize);
            static bool ok = true;
            int empty_space = 0;
            while (ba.at(empty_space) == '\0') {
                ++empty_space;
            }
            ba.remove(0, empty_space);
            m_gotCommandSize = ba.toLongLong(&ok, m_sizeFieldBase);
            //qDebug("%s size field %d", qPrintable(objectName()), m_gotCommandSize);
            m_gotCommandSize -= m_sizeFieldSize;
            Q_ASSERT(ok);
            Q_ASSERT(m_gotCommandSize >= 2);
        }
    }
    if (m_tcpConnection->bytesAvailable() > 0 && m_tcpConnection->bytesAvailable() >= m_gotCommandSize) {
        onReadyRead();
    }
}

void QRemoter::clientConnected()
{
    m_tcpConnection = m_tcpClient;
    Q_ASSERT(m_tcpConnection->isValid());
    qDebug("QRemoter::clientConnected() %s", qPrintable(objectName()));
    emit connected();
}

void QRemoter::updateClientProgress(qint64 p)
{
    Q_UNUSED(p);
    //qDebug("%s QRemoter::updateClientProgress(qint64 p = %d)", qPrintable(objectName()), (int)p);
}

void QRemoter::clientDisconnected()
{
    m_tcpConnection = 0;
    qDebug("QRemoter::clientDisconnected() %s" , qPrintable(objectName()));
    emit disconnected();
}

void QRemoter::displayError(QAbstractSocket::SocketError socketError)
{
    // NOTIFY CLIENTS
//    if (socketError == QTcpSocket::RemoteHostClosedError)
//             return;

//         QMessageBox::information(0, tr("Network error"),
//                                  tr("QRemoter: The following error occurred: %1.")
//                                  .arg(m_tcpConnection->errorString()));

         m_tcpClient->close();
         m_tcpServer->close();
         m_tcpConnection = 0;

         emit error(socketError);
}






