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

#ifndef QSTRINGPROTOCOL_H
#define QSTRINGPROTOCOL_H

#include "QAbstractProtocol.h"

class QStringProtocol : public QAbstractProtocol
{
    Q_OBJECT
public:
    explicit QStringProtocol(QObject *parent = 0);

    virtual QPair<QString, QVariant> decodeString(const QByteArray& str);
    virtual QByteArray encodeValue(const QString& command, const QVariant& v);

protected:
    QString variantToString(const QVariant& list, const unsigned short level);
    QVariant stringToVariant(const QString& str, const unsigned short level);

    static const QString m_separator;
    static const QString m_nullVariantString;
};

#endif // QSTRINGPROTOCOL_H
