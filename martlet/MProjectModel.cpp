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


#include "MProjectModel.h"
#include "MartletProject.h"
        
#include <QVariant>


using namespace std;
        
MProjectModel::MProjectModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_Project(0)
{
}

#define qDebug(...)

void MProjectModel::setProject(MartletProject* pro)
{
    beginResetModel();
    m_Project = pro;
    if (m_Project) {
        disconnect(m_Project, SIGNAL(projectChanged(int)), this, 0);
        connect(m_Project, SIGNAL(projectChanged(int)), this, SLOT(handleProjectChanges(int)));
        emit dataChanged(MProjectModel::index(0, 0, QModelIndex()), MProjectModel::index(rowCount(QModelIndex()), 0, QModelIndex()));
    }
    endResetModel();
}

void MProjectModel::handleProjectChanges(int suite)
{
    if(suite != -1) {
        beginResetModel();
        endResetModel();
    } else {
        emit dataChanged( MProjectModel::index(0, 0, QModelIndex()),
                          MProjectModel::index(rowCount(QModelIndex()), 0, QModelIndex()) );
    }
}

int	MProjectModel::columnCount ( const QModelIndex & /*parent*/ ) const
{
    return 1;
}

int	MProjectModel::rowCount ( const QModelIndex & parent ) const
{

    if (m_Project == 0 ) {
        return 0;
    }
    if (parent.isValid()) {
        TestItem *p = static_cast<TestItem *> (parent.internalPointer());
        qDebug("MProjectModel::rowCount() r = %d, c = %d count = %d", parent.row(), parent.column(), p->childrenItems().count());
        return p->childrenItems().count();
    } else {
        return 1;
    }
} 

bool MProjectModel::setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole )
{
    if (m_Project == 0) return false; 

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        TestItem *testItem = static_cast<TestItem *> (index.internalPointer());
        if (testItem) {
            testItem->setName(value.toString().toStdString());
            emit dataChanged(index, index);
        }
    }

    //TODO
    return false;
}

QVariant MProjectModel::data ( const QModelIndex & index, int role) const
{
    if (m_Project == 0)
        return QVariant();

    QVariant result;
    TestItem *testItem = static_cast<TestItem *> (index.internalPointer());
    if (testItem)
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
                result.setValue<QString>(QString::fromStdString(testItem->name()));
        }
        break;
        case Qt::DecorationRole:
        {
            result = testItem->icon();
        }
        break;
        case Qt::ToolTipRole:
        {
            result = testItem->toolTip();
        }
        break;

        }
    }

    return result;
}

Qt::ItemFlags MProjectModel::flags ( const QModelIndex & /*index*/ ) const
{
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex MProjectModel::index(int row, int column, const QModelIndex & parent) const
{
    if (m_Project != 0 ) {
        qDebug("index( r %d c %d isValid = %d)",row, column, int(parent.isValid()) );
        TestItem * parentTestItem = m_Project;
        if (parent.isValid()) {
            parentTestItem = static_cast<TestItem *> (parent.internalPointer());
            Q_ASSERT(parentTestItem->childrenItems().count() > row);
            TestItem *ch = parentTestItem->childrenItems()[row];
            return createIndex(row, column, ch);
        } else {
            return createIndex(row, column, parentTestItem); // root project item
        }
    }
    return QModelIndex();
}


QModelIndex	MProjectModel::parent ( const QModelIndex & child ) const
{
    TestItem* itm = static_cast<TestItem *> (child.internalPointer());
    if (itm && itm->hasParent()) {
        TestItem* p = itm->parentItem();
        int ridx = 0;
        if (p->hasParent()) {
            ridx = p->parentItem()->childrenItems().indexOf(p);
        }
        Q_ASSERT(ridx >= 0);
        return createIndex(ridx , child.column() ,  p);
    }
    return QModelIndex();
}

bool	MProjectModel::hasChildren ( const QModelIndex & parent) const
{
    if (m_Project == 0)
        return false;


    if (!parent.isValid() /*|| parent.internalId() < TREE_DEEP_STEP * TESTELEMENT*/) {
        return true;
    }

    qDebug("hasChildren ( r %d c %d )",parent.row(), parent.column() );
    TestItem const *testItem = static_cast<TestItem *> (parent.internalPointer());

    if (testItem ) {
        return testItem->hasChildren();
    }
    return false;
}

