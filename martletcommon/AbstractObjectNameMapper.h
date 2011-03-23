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


#ifndef ABSTRACTOBJECTNAMEMAPPER_H
#define ABSTRACTOBJECTNAMEMAPPER_H

#include <QObject>
#include <QPair>

class AbstractObjectNameMapper : public QObject
{
    Q_OBJECT

public:
    AbstractObjectNameMapper(QObject *parent);
    ~AbstractObjectNameMapper();

    /// Cahed variant of below functions
    QObject* getObjectFromName(const QString& name );
    QString makeCachedObjectName(QObject* obj );

protected:
    virtual QObject* objectFromName(const QString& name ) const = 0;
    virtual QString makeObjectName(QObject* obj ) const = 0;

    QPair<QObject*, QString> m_cachePair;

private:
    
};

#endif // ABSTRACTOBJECTNAMEMAPPER_H
