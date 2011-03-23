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


#include "MartletProject.h"
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>

#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>


QPixmap makeIcon(const QString& name)
{
    const QPixmap orig(name);
    return orig.scaled(32, 32);
}

MartletProject* MartletProject::m_instance = 0;


MartletProject::MartletProject()
    : type(this)
    , fileName(this)
    , executable(this)
    , m_isDirty(false)

{
    setName("Project");
    m_page = 0;
    m_icon = makeIcon(":/model/p.png");
    m_toolTip = "Project";

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

Suite* MartletProject::currentSuite() const
{
    return suites.front();
}

QDir MartletProject::projectDir() const
{
    const QFileInfo fi(QString::fromStdString(fileName.name()));
    return fi.absoluteDir();
}
bool MartletProject::isValid() const
{
    if (executable.name().empty()) return false;
    if (fileName.name().empty()) return false;
    if (type.name().empty()) return false;
    return true;
}

void MartletProject::loadFromFile(const  std::string& str )
{
    qDebug() << "Loading project from file "<< QString::fromStdString(str);
    Q_ASSERT(!str.empty());
    fileName.setName(str);

    try
    {
        std::ifstream ifs(fileName.name().c_str() /*, std::ios::in | std::ios::trunc*/);
        if (ifs.is_open()) {
            boost::archive::xml_iarchive xml(ifs);
            xml.register_type(static_cast<MartletProject*>(0));
            xml >> boost::serialization::make_nvp("MartletProject", *this);
        }
    }
    catch (boost::archive::archive_exception e)
    {
        QMessageBox::critical(0, "Error loading project",
                              QString("An error occured during loading project %1 \n\n%2\n").arg(QString::fromStdString(str)).arg(e.what()));
        qDebug(e.what());
        return;
    }

    type.setParent(this);
    executable.setParent(this);
    qDebug("Loaded %d suites", suites.size() );
    for (std::vector<Suite *>::iterator i = suites.begin(); i != suites.end(); ++i) {
        (*i)->setParent(this);
        qDebug("Add suite %s", qPrintable(QString::fromStdString((*i)->name())));

        for (std::vector<TestCase *>::iterator it = (*i)->testCases.begin() ; it != (*i)->testCases.end(); ++it) {
            (*it)->setParent(*i);
            qDebug("Add test case %s", qPrintable(QString::fromStdString((*it)->name())));

            for (std::vector<TestFile *>::iterator ft = (*it)->files.begin() ; ft != (*it)->files.end(); ++ft) {
                (*ft)->setParent(*it);
                qDebug("Add test file %s", qPrintable(QString::fromStdString((*ft)->name())));
            }
        }
    }
    m_isDirty = false;
}

void MartletProject::saveToFile(const  std::string& str)
{
    qDebug() << "Saving project to file "<< QString::fromStdString(fileName.name());
    Q_ASSERT(!str.empty());
    fileName.setName( str );

    std::ofstream ofs(fileName.name().c_str(), std::ios::out | std::ios::trunc);
    if (ofs.is_open()) {
        boost::archive::xml_oarchive xml(ofs);
        xml.register_type(static_cast<MartletProject*>(0));
        xml << boost::serialization::make_nvp("MartletProject", *this);
    }
    m_isDirty = false;
}

void MartletProject::save()
{
    saveToFile(fileName.name());
}


template<class archive>
void MartletProject::serialize(archive& ar, const unsigned int /*version*/)
{
    using boost::serialization::make_nvp;
    ar & make_nvp("Name", m_name);
    ar & make_nvp("Type", type.m_name);
    //ar & make_nvp("Filename", filename);
    ar & make_nvp("Executable", executable.m_name);
    ar & make_nvp("Suites", suites);
}

void MartletProject::notifyAboutChanges(int suiteIdx)
{
    emit projectChanged(suiteIdx);
}




TestItem::TestItem(TestItem * parent)
    : QObject(parent)
    , m_page(0)
    , m_icon (/*makeIcon(":/model/tk.png")*/)
    , m_toolTip("Node")
{
    setName("Unnamed TestItem");
}

int TestItem::page() const
{
    return m_page;
}

QPixmap TestItem::icon() const
{
    return m_icon;
}

QString TestItem::toolTip() const
{
    return m_toolTip;
}







TestFile::TestFile(TestItem *parent, const QString& name)
{
    setName(name.toStdString());
    setParent(parent);
    m_page = 1;
    m_icon = makeIcon(":/model/f.png");
    m_toolTip = "Script File";
}

TestFile::TestFile(){
    m_page = 1;
    m_icon = makeIcon(":/model/f.png");
    m_toolTip = "Script File";
}

template<class archive>
void TestFile::serialize(archive& ar, const unsigned int /*version*/)
{
    using boost::serialization::make_nvp;
    ar & make_nvp("Name", m_name);
}














TestCase::TestCase(TestItem *parent, const QString& name)
{
    setName(name.toStdString());
    setParent(parent);
    m_page = 0;
    m_icon = makeIcon(":/model/tk.png");
    m_toolTip = "Test Case";
}

TestCase::TestCase(){
    m_page = 0;
    m_icon = makeIcon(":/model/tk.png");
    m_toolTip = "Test Case";
}

template<class archive>
void TestCase::serialize(archive& ar, const unsigned int /*version*/)
{
    using boost::serialization::make_nvp;
    ar & make_nvp("Name", m_name);
    ar & make_nvp("Files", files);
//    ar & make_nvp("TestCases", m_pTestCases);
}








//// SUITE









Suite::Suite(TestItem *parent, const std::string& nm)
{
    setParent(parent);
    setName(nm);
    m_page = 0;
    m_icon = makeIcon(":/model/s.png");
    m_toolTip = "Tests Suite";
}

Suite::~Suite()
{
//    for(unsigned int i = 0;i< m_pTestCases.size(); ++i){
//        delete m_pTestCases[i];
//    }
}

template<class archive>
void Suite::serialize(archive& ar, const unsigned int /*version*/)
{
    using boost::serialization::make_nvp;
    ar & make_nvp("Name", m_name);
//    ar & make_nvp("File", file);
    ar & make_nvp("TestCases", testCases);
}








