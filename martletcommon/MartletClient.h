//    Martlet - application automated Qt GUI application testing and more.
//    Copyright (C) 2010  Oleksandr Omelchuk sashao@e-mail.ua

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#ifndef MARTLETCLIENT_H
#define MARTLETCLIENT_H

#include <QObject>
#include <QVariant>

class QRemoter;
        
class MartletClient : public QObject
{
    Q_OBJECT
public:
    enum ClientMode {
        None,
        StartingApp,
        RunningScript
    };
    
    MartletClient();
    ~MartletClient();
    
    bool startListening();
    bool isConnected();
    QRemoter* client();

public:
     void uploadScript(const QString& relativePath, const QString& scriptLines);
     void play(const QString& relativePath);
     
     void startRecording(QString fname);
     void stopRecording(QString fname);
     // TODO: temporary thing. Remove this.
     void askForRecordedText(QString fname);
     
     // SPY
     void startSpy();
     void stopSpy();
    
signals:
    void aplicationStarted(int portID);
    void recordedTextArrived(const QVariant& text);

private slots:
//    void processReturnValue( int requestId, QVariant value );
//    void processFault( int requestId, int errorCode, QString errorString );
    void onPlaybackFinished();

private:
    /// Communicates with remote app
    QScopedPointer<QRemoter> m_client;
    /// Comunicates with daemon, starts app
    QScopedPointer<QRemoter> m_appClient;
    
    int textId;
};

#endif // MARTLETCLIENT_H
