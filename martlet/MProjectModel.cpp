#include "MProjectModel.h"
#include "MartletProject.h"
        
#include <QVariant>

using namespace std;
        
MProjectModel::MProjectModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_Project(0)
{
}


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

bool MProjectModel::setData ( const QModelIndex & /*index*/, const QVariant & /*value*/, int role = Qt::EditRole )
{
    Q_UNUSED(role);
    if (m_Project == 0) return false; 
    
    //TODO
    return false;
}

QVariant MProjectModel::data ( const QModelIndex & index, int role) const
{
    if (m_Project == 0)
        return QVariant();

    QVariant result;
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        TestItem *testItem = static_cast<TestItem *> (index.internalPointer());
        if (testItem) {
            result.setValue<QString>(QString::fromStdString(testItem->name()));
        }
    }

    /*if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (index.row() == 0) {
            result.setValue<QString>(QString::fromStdString(m_Project->fileName));
        } else if (index.internalId() >= SUITE * SUITE && index.internalId() < TREE_DEEP_STEP * TESTCASE) {
            const int suiteID = index.internalId();
            result.setValue<QString>(QString::fromStdString(m_Project->suites.at(suiteID).name));
        }// ... continue
    }*/
    return result;
}

/*QVariant MProjectModel::data ( const QModelIndex & index, int role) const
{
    if (m_Project == 0) return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
//        qDebug("2 Requested data for row %d, col %d role = %d ID = %d", index.row(), index.column(), int(role), index.internalId());
        QVariant result;
        if (index.internalId() >= 1000) {   // SUITE sub properties
            const int suiteID = index.internalId()-1000;            
            if (index.column() == 1) {
                switch(index.row()) {
                case 0:
                    result.setValue<QString>(QString::fromStdString(m_Project->suites.at(suiteID).name));
                    break;
                case 1:
                    result.setValue<QString>(QString::fromStdString(m_Project->suites.at(suiteID).file));
                    break;
                }
            }
            else
            {
                switch(index.row()) {
                case 0:
                    result.setValue<QString>("name");
                    break;
                case 1:
                    result.setValue<QString>("file");
                    break;
                }
            }
        } 
        else 
        {
            if ( index.row() >= SUITEFIRST && index.internalId() >= 0) {
                if (index.column() == 1) {
                    result.setValue<QString>(QString::fromStdString(m_Project->suites.at(index.row()-SUITEFIRST).name) );
                } else {
                    result.setValue<QString>("Suite:");
                }
            } else 
            {
                if (index.column() == 1) {
                    switch(index.row()) {
                    case FILENAME:
                        result.setValue<QString>(QString::fromStdString(m_Project->fileName));
                        break;
                    case TYPE:
                        result.setValue<QString>(QString::fromStdString(m_Project->type));
                        break;
                    case EXE:
                        result.setValue<QString>(QString::fromStdString(m_Project->executable));
                        break;
                    default:
                        qWarning("Unhandled row index");
                        break;
                    }
                } else {
                    switch(index.row()) {
                    case FILENAME:
                        result.setValue<QString>("Filname:");
                        break;
                    case TYPE:
                        result.setValue<QString>("Type:");
                        break;
                    case EXE:
                        result.setValue<QString>("Exe name:");
                        break;
                    default:
                        qWarning("Unhandled row index");
                        break;
                    }

                }
            }
        }
        return result;
    }
//    qDebug("1 Requested data for row %d, col %d role = %d", index.row(), index.column(), int(role));
    return QVariant();
}*/

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

