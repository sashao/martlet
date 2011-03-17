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

#include "QRemoterSignalsWatcer.h"
#include "QRemoter.h"

QRemoterSignalsWatcer::QRemoterSignalsWatcer(QRemoter *parent,
                                             const QString& name,
                                             const int params)
    : QObject(parent)
    , commandName(name)
    , m_remoter(parent)
    , m_paramsCount(params)
{
    Q_ASSERT(params >= 0);
    Q_ASSERT(params <= 3);
}

void QRemoterSignalsWatcer::notifyAboutResponce(const QVariant& v)
{
    switch (m_paramsCount) {
    case 0:
        emit gotResponce();
        break;
    case 1:
        emit gotResponce1(v);
        break;
    case 2:
        {
            Q_ASSERT( v.canConvert(QVariant::List) );
            QVariantList vl = v.toList();
            Q_ASSERT( vl.count() == 2 );
            emit gotResponce2(vl[0], vl[1]);
        }
        break;
    case 3:
        {
            Q_ASSERT(v.canConvert(QVariant::List));
            QVariantList vl = v.toList();
            Q_ASSERT(vl.count() == 3);
            emit gotResponce3(vl[0], vl[1], vl[2]);
        }
        break;
    }
}

int QRemoterSignalsWatcer::paramsCount() const
{
    return m_paramsCount;
}

void QRemoterSignalsWatcer::sendCommand()
{
    m_remoter->perform(commandName);
}

void QRemoterSignalsWatcer::sendCommand1(const QVariant& v)
{
    m_remoter->perform(commandName, v);
}

void QRemoterSignalsWatcer::sendCommand2(const QVariant& v1, const QVariant& v2)
{
    QVariantList vl;
    vl << v1 << v2;
    sendCommand1(vl);
}

void QRemoterSignalsWatcer::sendCommand3(const QVariant& v1, const QVariant& v2, const QVariant& v3)
{
    QVariantList vl;
    vl << v1 << v2 << v3;
    sendCommand1(vl);
}



