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
