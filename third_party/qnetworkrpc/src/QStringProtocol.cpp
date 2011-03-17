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

#include "QStringProtocol.h"
#include <QVariant>
#include <QByteArray>
#include <QStringList>
#include <QDebug>

#define qDebug(...)

const QString QStringProtocol::m_separator = "<!@&_%1_^$#>";
const QString QStringProtocol::m_nullVariantString = "<|QStringProtocol:NULL|>";

QStringProtocol::QStringProtocol(QObject *parent) :
    QAbstractProtocol(parent)
{
}

QVariant QStringProtocol::stringToVariant(const QString& str, const unsigned short level)
{
    const QStringList pslist = str.split(m_separator.arg(level));
    QVariant v;
    if ( pslist.isEmpty() ) {
        // null variant
        qDebug("Empty string %s", qPrintable(str));
    } else if (pslist.size() == 1) {
        qDebug("One string %s", qPrintable(str));
        if (pslist.front() != m_nullVariantString) {
            v = QVariant(pslist.front());
            qDebug("One good string %s", qPrintable(str));
        }
    } else {
        QVariantList vl;
        foreach ( QString s, pslist) {
            vl.append(stringToVariant(s, level+1));
        }
        v = vl;
    }
    return v;
}

QPair<QString, QVariant> QStringProtocol::decodeString(const QByteArray& commandStr)
{
    const int nameSize = static_cast<int>(commandStr.at(0));
    Q_ASSERT(nameSize > 0);
    const QString name = commandStr.mid(1, nameSize );
    const QString paramsStr = QString::fromUtf8(
            commandStr.mid(1+nameSize, commandStr.size() - 1 - nameSize - 1 ) );
    Q_ASSERT( commandStr.at(commandStr.size()-1) == '\0' );

    const QVariant params = stringToVariant(paramsStr, 0);
    //qDebug() << "params   " << params;

    return qMakePair<QString, QVariant>(name, params);
}


QString QStringProtocol::variantToString(const QVariant& list, const unsigned short level)
{
    if (list.type()==QVariant::List) {
        QStringList sl;
        const QVariantList vl = list.toList();
        foreach(QVariant i, vl) {
            sl.append(variantToString(i, level+1));
        }
        return sl.join(m_separator.arg(level));
    } else if (list.type() == QVariant::Invalid) {
        qDebug("Variant %s", qPrintable(list.toString()));
        return m_nullVariantString;
    } else if (list.canConvert(QVariant::String)) {
        return list.toString().toUtf8();
    } else {
        Q_ASSERT_X(false, "Cant convert given variant to string ", list.typeName());
    }
    return QString();
}

QByteArray QStringProtocol::encodeValue(const QString& command, const QVariant& params)
{
    QByteArray data;
    Q_ASSERT( !command.isEmpty() );
    Q_ASSERT( command.size() < 255 );
    data.append( static_cast<char>(command.size()) ); // size of command name
    data.append( command ); // command name

    data.append(variantToString(params, 0)); // parameters data
    data.append( static_cast<char>(0) ); // control zero byte
    return data;
}


