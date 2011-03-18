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
