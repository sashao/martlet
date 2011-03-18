#include "QObjectPropertyModel.h"
#include <QMetaProperty>

QObjectPropertyModel::QObjectPropertyModel(QObject *parent) :
    QAbstractTableModel(parent)
    , m_obj(parent)
{

}

void QObjectPropertyModel::setObject(QObject* obj)
{
    m_obj = obj;
    reset();
}


int	QObjectPropertyModel::columnCount ( const QModelIndex & parent) const
{
    return 2;
}

int	QObjectPropertyModel::rowCount ( const QModelIndex & parent) const
{
    return m_obj->metaObject()->propertyCount();
}

bool	QObjectPropertyModel::setData ( const QModelIndex & index, const QVariant & value, int role)
{
    const QMetaProperty mp = m_obj->metaObject()->property(index.row());
    mp.write(m_obj, value);
    emit dataChanged(index, index);
}

QVariant	QObjectPropertyModel::data ( const QModelIndex & index, int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole) {
        const QMetaProperty mp = m_obj->metaObject()->property(index.row());
        if (index.column() == 0) {
            return mp.name();
        } else {
            return mp.read(m_obj);
        }
    }
    return QVariant();
}

Qt::ItemFlags QObjectPropertyModel::flags ( const QModelIndex & index ) const
{
    Qt::ItemFlags f = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    const QMetaProperty mp = m_obj->metaObject()->property(index.row());
    if (mp.isWritable()) f |= Qt::ItemIsEditable;


    return f;

}
