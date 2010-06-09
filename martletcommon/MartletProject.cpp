#include "MartletProject.h"
#include <QTextStream>
#include <QDebug>


MartletProject* MartletProject::m_instance = 0;


MartletProject::MartletProject():
        m_doc("martlet")
{
    m_isDirty = false;
}

MartletProject::~MartletProject()
{
    
}

MartletProject* MartletProject::getCurrent()
{
    return m_instance;
}

void MartletProject::setCurrent(MartletProject* pro)
{
    m_instance = pro;
}

bool MartletProject::isValid()
{
    if (executable.isEmpty()) return false;
    if (fileName.isEmpty()) return false;
    if (type.isEmpty()) return false;
    return true;
}

void MartletProject::loadFromFile(const  QString& str )
{
    Q_ASSERT(str.isEmpty());
    fileName = str;
    QFile file(fileName);
     if (!file.open(QIODevice::ReadOnly))
         return;
     if (!m_doc.setContent(&file)) {
         file.close();
         return;
     }
     file.close();    
     
     load();
}

void MartletProject::saveToFile(const  QString& str)
{
    Q_ASSERT(!str.isEmpty());
    fileName = str;
    QFile f(fileName);
//    Q_ASSERT(f.exists()); // TODO: owerwrite dialog
    if (!f.open(QIODevice::WriteOnly)) {
        Q_ASSERT(f.isOpen());
        return;
    }

    QTextStream stream(&f);
    m_doc.save(stream, 4);
    
    f.close();
}

void MartletProject::save()
{
    saveSettings();
    
    Suite s;
    foreach(s, suites) {
        s.save(m_doc);
    }
    qDebug() << "Saving project to file "<< fileName<< " with contents:\n" << m_doc.toString();
    saveToFile(fileName);
}

void MartletProject::load()
{
    loadSettings();
    
    // load each suite
    QDomNodeList list = m_doc.elementsByTagName("Suite");
    for(int i = 0; list.count(); ++i) {
        QDomNode node(list.at(i));
        if (node.isElement()) {
            QDomElement element(node.toElement());
            qDebug()<< "Loading node"<< node.nodeName();
            Suite s;
            s.load(element);
            suites.append(s);
        }
    }
}

void MartletProject::saveSettings()
{
    QDomElement my = m_doc.createElement("settings");
    my.setAttribute("executable", executable );
    my.setAttribute("type", type);
    m_doc.appendChild(my);        
}

void MartletProject::loadSettings()
{
    QDomElement root = m_doc.firstChildElement("");
    type = root.attribute("type","");
    Q_ASSERT(!type.isEmpty());
    
    executable = root.attribute("executable","");
    Q_ASSERT(!executable.isEmpty());
}









//// SUITE









MartletProject::Suite::Suite(const QString& nm, const QString& fl)
{
    name = nm;
    file = fl;
}

void MartletProject::Suite::load(const  QDomElement& root)
{
    name = root.attribute("name","");
    Q_ASSERT(!name.isEmpty());
    file = root.attribute("file","");
    Q_ASSERT(!file.isEmpty());
}

void MartletProject::Suite::save(QDomDocument& doc) const
{
    QDomElement my = doc.createElement("Suite");
    my.setAttribute("name", name);
    my.setAttribute("file", file);
    doc.appendChild(my);
}











