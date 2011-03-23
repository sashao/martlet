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


#include "ObjectNameMapper.h"
#include <QApplication>
#include <QWidget>

const QChar ObjectNameMapper::delimiter     = '.';
const QChar ObjectNameMapper::open_bracket  = '(';
const QChar ObjectNameMapper::close_bracket = ')';


ObjectNameMapper::ObjectNameMapper(QObject *parent)
    : AbstractObjectNameMapper(parent)
{

}

ObjectNameMapper::~ObjectNameMapper()
{

}

QObject* ObjectNameMapper::objectFromName(const QString& path ) const
{
    Q_ASSERT(!path.isEmpty());
    QObject* obj = 0;
    QStringList names = path.split(delimiter, QString::KeepEmptyParts);
    Q_ASSERT(names.size()>1);
    QStringList::const_iterator iname = names.constBegin();
    ++iname; // omit allways empty first string before leading delimmiterdeli
    QObjectList olist;
    foreach (QWidget* w, QApplication::topLevelWidgets()) {
        olist.append(w);
    }
    for( ;iname != names.constEnd(); ++iname )
    {
        QString name = (*iname);
        int searchedNum = 1;
        if (name.contains(open_bracket) && name.contains(close_bracket)){
            // TODO: handle various connversion/extracting exceptions
            // guess number in the brackets
            const int left = name.indexOf(open_bracket);
            Q_ASSERT(left != -1);
            const int right = name.indexOf(close_bracket, left);
            Q_ASSERT(right != -1);
            Q_ASSERT(left < right);
            const QString num = name.mid(left+1, right-left-1);
            Q_ASSERT(! num.isEmpty());
            searchedNum = num.toInt();
            Q_ASSERT(searchedNum > 0);
            // sanity name to search
            name.chop(name.length()-left);
        }
        // search for our object
        int num = 0;
        foreach (QObject* iobj, olist)
        {
            if (iobj->objectName() == name)
            {
                ++num;
                obj = iobj;
                if (searchedNum == num){
                    break;
                }
            }
        }
        olist = obj->children();
    }
    if (!obj) {
        qDebug("Unable to find object with name '%s'", qPrintable(path));
    }
    return obj;
}

QString ObjectNameMapper::makeObjectName(QObject* obj ) const
{
    // Name spec
    // Domain names with delimiter char '.'
    // Always Should start with delimiter character
    // Eg. .top_level_parent.group_box.frame(1).button_ok
    // Simple name could be empty string.
    // if object name is not unique optionaly index of this object may be specified in brackets "(1-n)"
    // Eg. .parent.groupBox(2).startButton
    // Eg. .parent.(2).startButton
    QString namePath;
    QObject* object = obj;
    while (object)
    {
        QObject* parent = object->parent();
        if (parent)
            // Find unique name among parent's children
        {
            // TODO: mask delimiter char '.'
            QString name = object->objectName();

            // Find "brothers" and "sisters" with the same name if any
            QObject* child = 0;
            const QObjectList& pchildren = parent->children();
            int inum = 0; // index in children list with the same name
            int anum = 0; // How many childrens
            foreach (child, pchildren)
            {
                if (child->objectName() == name) {
                    ++anum;
                    if (child == object) {
                        inum = anum;
                    }
                    //qDebug("%d/%d %s (%s)", inum, anum, qPrintable(object->objectName()), object->metaObject()->className());
                }
            }
            // add brackets if needed
            if ((inum > 0) && (anum > 1)) {
                name.append(open_bracket);
                name.append(QString::number(inum));
                name.append(close_bracket);
            }
            // update whole path
            namePath.prepend(name);
            namePath.prepend(delimiter);
            // do loop again
            object = parent;
        }
        else
        {
            namePath.prepend(object->objectName());
            namePath.prepend(delimiter);
            object = 0;
            break;
        }
    }
    return namePath;
}






