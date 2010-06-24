#include "MProjectModel.h"
#include "MartletProject.h"
        
#include <QVariant>
        
MProjectModel::MProjectModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_Project(0)
{
}


void MProjectModel::setProject(MartletProject* pro)
{
    beginResetModel();
    m_Project = pro;
    endResetModel();
}



int	MProjectModel::columnCount ( const QModelIndex & parent = QModelIndex() ) const
{
//    if (m_Project == 0) return 0;
    return 2;
}

int	MProjectModel::rowCount ( const QModelIndex & parent = QModelIndex() ) const
{
    if (m_Project == 0) return 0;    
    int rows = SUITEFIRST+m_Project->suites.size();
    if (parent.isValid() && parent.internalId() != -1) rows = 2; // SUITE
    qDebug("Model has %d rows", rows);
    return rows;
} 

bool	MProjectModel::setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole )
{
    if (m_Project == 0) return false; 
    
    //TODO
    return false;
}

QVariant	MProjectModel::data ( const QModelIndex & index, int role = Qt::DisplayRole ) const
{
    if (m_Project == 0) return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        qDebug("2 Requested data for row %d, col %d role = %d ID = %d", index.row(), index.column(), int(role), index.internalId());
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
}

QModelIndex	MProjectModel::index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const
{
    if (m_Project == 0) return QModelIndex();
    
    int suiteIndex = -1;
    if (row>=SUITEFIRST && !parent.isValid())  {
//        qDebug("SUITE VERY TREE NODE !!!!!!!!!!!");
        suiteIndex = row-SUITEFIRST;
    } else if (parent.isValid() && parent.internalId() >= 0 && parent.internalId() < 1000) {
//        qDebug("SUITE CHILDS !!!!!!!!!!!!!!!!!!!!!");
        suiteIndex = 1000+(parent.internalId());
    }
    qDebug("!!!!!!!!!!!!!!!!!!!! index row %d col %d   ID = %d", row, column, suiteIndex);
    return createIndex(row, column, suiteIndex);
}


bool	MProjectModel::hasChildren ( const QModelIndex & parent = QModelIndex() ) const
{
    if (m_Project == 0) return false;
//    qDebug("hasChildren row %d col %d", parent.row(), parent.column());
    if (parent.internalId() >= 1000) return false; // suite children
    if (parent.internalId() != -1 ) return true; // SUITE level 1
    if (!parent.isValid()) return true;
    return false;
}

QModelIndex	MProjectModel::parent ( const QModelIndex & index ) const
{
//    qDebug("parent row %d col %d ID = %d", index.row(), index.column(), index.internalId());
    if (m_Project == 0) return QModelIndex();    
    if (index.internalId() >= 1000) {
        const int suiteID = index.internalId()-1000;
//        qDebug("!!!!!!!!!!!!!! %d \n\n", suiteID);
        return createIndex(SUITEFIRST+suiteID, index.column() ,suiteID);
    }
    return QModelIndex();
}
