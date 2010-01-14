#ifndef OBJECTNAMEMAPPER_H
#define OBJECTNAMEMAPPER_H

#include <QObject>

class ObjectNameMapper : public QObject
{
    Q_OBJECT

public:
    ObjectNameMapper(QObject *parent);
    ~ObjectNameMapper();

    QObject* objectFromName(const QString& name ) const;
    QString makeObjectName(const QObject* obj ) const;

private:
    
};

#endif // OBJECTNAMEMAPPER_H
