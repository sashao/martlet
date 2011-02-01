#ifndef MPROJECTMODEL_H
#define MPROJECTMODEL_H

#include <QAbstractItemModel>
#include "MartletProject.h"


class MartletProject;

class MProjectModel : public QAbstractItemModel
{
Q_OBJECT
public:

    // TODO: remove this enum
    enum {
        FILENAME = 0,
        TYPE,
        EXE,
        SUITEFIRST
    };

    static const long double TREE_DEEP_STEP = 100;

    enum {
        PROJECT_NAME = 0,
        SUITE,
        TESTCASE,
        TESTELEMENT

    } ProjectTreeOrder;

    MProjectModel(QObject *parent = 0);
    
    void setProject(MartletProject* pro);

    virtual int	columnCount ( const QModelIndex & parent) const;
    virtual int	rowCount ( const QModelIndex & parent) const;
    virtual bool	setData ( const QModelIndex & index, const QVariant & value, int role);
    virtual QVariant	data ( const QModelIndex & index, int role) const;
    virtual QModelIndex	index ( int row, int column, const QModelIndex & parent) const;
    
    
    virtual bool	hasChildren ( const QModelIndex & parent) const;
    virtual QModelIndex	parent ( const QModelIndex & index ) const;

signals:

protected slots:
    void handleProjectChanges(int suite);
    
private:
    MartletProject* m_Project;

};

#endif // MPROJECTMODEL_H
