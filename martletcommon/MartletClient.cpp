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


#include "MartletClient.h"
#include "qnetworkrpc/src/QRemoter.h"
#include "RequestToRemote.h"

#include <QMessageBox>
#include <QApplication>

__declspec(dllexport) MartletClient::MartletClient()
  : textId(-1)
{
    m_client.reset( new QRemoter(this) );
    
//    connect( client(), SIGNAL(done( int, QVariant )),
//             this, SLOT(processReturnValue( int, QVariant )) );
//    connect( client(), SIGNAL(failed( int, int, QString )),
//             this, SLOT(processFault( int, int, QString )) );

    client()->connectRemoteSignal(RECORDING_OUTPUT_1, this,
                                  SIGNAL(recordedTextArrived(QVariant)));
    client()->connectRemoteSignal(PLAYBACK_FINISHED_0, this,
                                  SLOT(onPlaybackFinished()));
}

__declspec(dllexport) MartletClient::~MartletClient()
{

}

__declspec(dllexport) bool MartletClient::startListening()
{
    qDebug(Q_FUNC_INFO);
    if (!client()->isConnected()) {
        client()->listen( 2877 );
    }

    qDebug("MartletClient::tryConnect() Ceck if connected .. ");
    return isConnected();
}

__declspec(dllexport) bool MartletClient::isConnected()
{
    return client()->isConnected();
}

//void MartletClient::disconnect()
//{
//    client()->;
//}

__declspec(dllexport) QRemoter* MartletClient::client()
{
    return m_client.data();
}

__declspec(dllexport) void MartletClient::uploadScript(const QString& relativePath, const QString& scriptLines)
{
    client()->perform(PLAYBACK_UPLOAD_2, relativePath, scriptLines);
}

__declspec(dllexport) void MartletClient::play(const QString& relativePath)
{
    client()->perform(PLAYBACK_PLAY_1, relativePath );
}

     
__declspec(dllexport) void MartletClient::startRecording(QString fname)
{
    client()->perform(RECORDING_START_1, fname);
}

__declspec(dllexport) void MartletClient::stopRecording(QString fname)
{
    client()->perform(RECORDING_STOP_1, fname);
}

__declspec(dllexport) void MartletClient::askForRecordedText(QString fname)
{
    client()->perform(RECORDING_GET_1, fname);
}

__declspec(dllexport) void MartletClient::onPlaybackFinished()
{
    client()->perform(APP_QUIT_0);
}


__declspec(dllexport) void MartletClient::startSpy()
{
    client()->perform(SPY_START_0);
}

__declspec(dllexport) void MartletClient::stopSpy()
{
    client()->perform(SPY_STOP_0);
}


