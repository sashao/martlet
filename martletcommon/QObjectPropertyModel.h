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


#ifndef QOBJECTPROPERTYMODEL_H
#define QOBJECTPROPERTYMODEL_H

#include <QAbstractTableModel>
#include <QPointer>

class QObjectPropertyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit QObjectPropertyModel(QObject *parent = 0);

    void setObject(QObject* obj);

    virtual int	columnCount ( const QModelIndex & parent) const;
    virtual int	rowCount ( const QModelIndex & parent) const;
    virtual bool	setData ( const QModelIndex & index, const QVariant & value, int role);
    virtual QVariant	data ( const QModelIndex & index, int role) const;
    virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;

signals:

public slots:

private:
    QPointer<QObject> m_obj;
};

#endif // QOBJECTPROPERTYMODEL_H
