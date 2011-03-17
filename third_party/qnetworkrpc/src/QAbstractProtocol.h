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

#ifndef QABSTARCTPROTOCOL_H
#define QABSTARCTPROTOCOL_H

#include <QObject>
#include <QPair>

class QAbstractProtocol : public QObject
{
    Q_OBJECT
public:
    explicit QAbstractProtocol(QObject *parent = 0);

    virtual QPair<QString, QVariant> decodeString(const QByteArray& str) = 0;
    virtual QByteArray encodeValue(const QString& command, const QVariant& v) = 0;

    virtual ~QAbstractProtocol();
};

#endif // QABSTARCTPROTOCOL_H
