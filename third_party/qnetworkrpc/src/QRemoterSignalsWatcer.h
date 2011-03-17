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

#ifndef QREMOTERSIGNALSWATCER_H
#define QREMOTERSIGNALSWATCER_H

#include <QObject>

class QRemoter;

class QRemoterSignalsWatcer : public QObject
{
    Q_OBJECT
private:
    friend class QRemoter;
    explicit QRemoterSignalsWatcer(QRemoter *parent, const QString& name,
                                   const int params);
    void notifyAboutResponce(const QVariant& v);
    int paramsCount() const;

signals:
    void gotResponce();
    void gotResponce1(const QVariant& v);
    void gotResponce2(const QVariant& v1, const QVariant& v2);
    void gotResponce3(const QVariant& v1, const QVariant& v2, const QVariant& v3);

public slots:
    void sendCommand();
    void sendCommand1(const QVariant& v);
    void sendCommand2(const QVariant& v1, const QVariant& v2);
    void sendCommand3(const QVariant& v1, const QVariant& v2, const QVariant& v3);

private:
    const QString commandName;
    QRemoter * const m_remoter;
    const int m_paramsCount;
};

#endif // QREMOTERSIGNALSWATCER_H
