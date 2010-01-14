#include "ObjectNameMapper.h"
#include <QApplication>
#include <QWidget>

ObjectNameMapper::ObjectNameMapper(QObject *parent)
    : QObject(parent)
{

}

ObjectNameMapper::~ObjectNameMapper()
{

}

QObject* ObjectNameMapper::objectFromName(const QString& name ) const
{
    QObject* obj = QApplication::activeWindow()->findChild<QObject*>(name);
    if (!obj) {
        qDebug("Unable to find object with name '%s'", qPrintable(name));
    }
    return obj;
}

QString ObjectNameMapper::makeObjectName(const QObject* obj ) const
{
    const QChar delimiter = '.';
    QString namePath;
    QObject* object = obj;
    while (object)
    {
        QObject* parent = obj->parent();
        if (parent)
            // Find unique name among parent's children
        {
            const QString name = object->objectName();
            namePath.append(delimiter);
            QObject* child = 0;
            const QObjectList& pchildren = children();
            int num = 0; // How many childrens
            foreach (child, pchildren)
            {
                if (child->objectName() == name) {
                    ++num;
                    if (child == object) {
                        break;
                    }
                }
            }
            if (num > 0) {
                name.append('(');
                name.append(QString::number(num));
                name.append(')');
            }
        }
        else
            // this object is toplevel widget
        {
            object = 0;
            break;
        }
    }
    return namePath;
}






