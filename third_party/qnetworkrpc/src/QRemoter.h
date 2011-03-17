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

#ifndef QREMOTER_H
#define QREMOTER_H

#include <QObject>
#include <QAbstractSocket>
#include <QVariant>

class QTcpServer;
class QTcpSocket;
class QRemoterSignalsWatcer;
class QAbstractProtocol;

/**
  * @class QRemoter is a base class for communication.
  *
  **/
class QRemoter : public QObject
{
    Q_OBJECT
public:
    explicit QRemoter(QObject *parent = 0);
    virtual ~QRemoter();

    void listen(quint16 port);
    void connectToHost ( const QString & hostName, quint16 port);
    bool isConnected();
    void stopConnecting();

    template <class T>
    void perform()
    {
        perform( T::staticMetaObject.className());
    }
    template <class T>
    void perform(const QVariant& l)
    {
        perform( T::staticMetaObject.className(), l);
    }
    template <class T>
    void perform(const QVariant& l1, const QVariant& l2)
    {
        perform( T::staticMetaObject.className(), l1, l2);
    }
    template <class T>
    void perform(const QVariant& l0, const QVariant& l1, const QVariant& l2)
    {
        perform( T::staticMetaObject.className(), l0, l1, l2);
    }
    void perform(const QString& name, const QVariant& l);
    // convenience methods
    void perform(const QString& name );
    void perform(const QString& name, const QVariant& a1, const QVariant& a2);
    void perform(const QString& name, const QVariant& a1, const QVariant& a2, const QVariant& a3);

    template <class T>
    bool connectSignalToRemote(const QObject * sender, const char * signal)
    {
        return connectSignalToRemote(sender, signal, T::staticMetaObject.className());
    }

    template <class T>
    bool connectRemoteSignal(const QObject * receiver, const char * method)
    {
        return connectRemoteSignal(T::staticMetaObject.className(), receiver, method);
    }

    bool connectSignalToRemote(const QObject * sender,
                               const char * signal,
                               const QString& commandName );
    bool connectRemoteSignal(const QString& commandName,
                             const QObject * receiver,
                             const char * method );
    /**
      * QRemoter takes ownership of this protocol
      */
    void setProtocol(QAbstractProtocol* newProtocol);

signals:
    void connected();
    void disconnected();
    void failedToConnect();
    void error(QAbstractSocket::SocketError socketError);

protected slots:
    void acceptConnection();
    void clientConnected();
    void updateClientProgress(qint64);
    void onClientHostFound();
    void clientDisconnected();
    void displayError(QAbstractSocket::SocketError);
    void onReadyRead();

protected:
    void handleReceivedCommand(const QString& commandName, const QVariant& params );

    QTcpServer *m_tcpServer;
    QTcpSocket *m_tcpClient;
    QTcpSocket *m_tcpConnection;
    // receive flag
    long long m_gotCommandSize;
    static const int m_sizeFieldSize;
    static const int m_sizeFieldBase;
    QAbstractProtocol* m_protocol;

    QMap< QString, QRemoterSignalsWatcer* > m_connectionsMap;

};

#endif // QREMOTER_H
