#ifndef OBJECTNAMEMAPPER_H
#define OBJECTNAMEMAPPER_H

#include "AbstractObjectNameMapper.h"

class ObjectNameMapper : public AbstractObjectNameMapper
{
    Q_OBJECT

public:
    ObjectNameMapper(QObject *parent);
    ~ObjectNameMapper();

    QObject* objectFromName(const QString& name ) const;
    QString makeObjectName(QObject* obj ) const;

private:
    static const QChar delimiter, open_bracket, close_bracket;
    
};

#endif // OBJECTNAMEMAPPER_H
