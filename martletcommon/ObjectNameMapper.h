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


#ifndef OBJECTNAMEMAPPER_H
#define OBJECTNAMEMAPPER_H

#include "AbstractObjectNameMapper.h"

class ObjectNameMapper : public AbstractObjectNameMapper
{
    Q_OBJECT

public:
    ObjectNameMapper(QObject *parent);
    ~ObjectNameMapper();

    QObject* objectFromName(const QString& name ) const;
    QString makeObjectName(QObject* obj ) const;

private:
    static const QChar delimiter, open_bracket, close_bracket;
};

#endif // OBJECTNAMEMAPPER_H
