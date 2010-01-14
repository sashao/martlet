#ifndef ABSTRACTOBJECTNAMEMAPPER_H
#define ABSTRACTOBJECTNAMEMAPPER_H

#include <QObject>

class AbstractObjectNameMapper : public QObject
{
    Q_OBJECT

public:
    AbstractObjectNameMapper(QObject *parent);
    ~AbstractObjectNameMapper();

    virtual QObject* objectFromName(const QString& name ) const = 0;
    virtual QString makeObjectName(QObject* obj ) const = 0;

private:
    
};

#endif // ABSTRACTOBJECTNAMEMAPPER_H
