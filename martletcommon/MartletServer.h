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


#ifndef MARTLETSERVER_H
#define MARTLETSERVER_H

#include <QObject>
#include <QMap>
#include <QVariant>
#include "EventCatcher.h"
#include "qnetworkrpc/src/QRemoter.h"

/**
  * Execute comands on testable app.
  */
class MartletServer : public QObject
{
    Q_OBJECT
public:
    MartletServer( void (*spy)(QObject*) );
    QRemoter *client();

private slots:
    void connected();
    void disconnected();

    void uploadScript(const QVariant& relativePath, const QVariant& scriptLines);
    void play(const QVariant& relativePath);
    void stopPlayback();

    void startSpy();
    void stopSpy();

    void quit();

    //     RECORDING RELATED
    void record(const QVariant& suiteName);
    void stopRecording(const QVariant& suiteName);
    void getRecordedText(const QVariant& suiteName);

private:
    QScopedPointer<QRemoter> m_server;
    EventCatcher m_catcher;
    QMap<QString, QString> m_filesystem;
};

#endif // MARTLETSERVER_H
