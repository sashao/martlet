#include "AbstractObjectNameMapper.h"

AbstractObjectNameMapper::AbstractObjectNameMapper(QObject *parent)
    : QObject(parent)
{

}

AbstractObjectNameMapper::~AbstractObjectNameMapper()
{

}

QObject* AbstractObjectNameMapper::getObjectFromName(const QString& name )
{
    if (m_cachePair.second != name){
        m_cachePair.first = objectFromName(name);
        m_cachePair.second = name;
    }
    return m_cachePair.first;
}

QString AbstractObjectNameMapper::makeCachedObjectName(QObject* obj )
{
    if (m_cachePair.first != obj){
        m_cachePair.first = obj;
        m_cachePair.second = makeObjectName(obj);
    }
    return m_cachePair.second;
}
