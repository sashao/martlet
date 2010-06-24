#include "MartletProject.h"
#include <QTextStream>
#include <QDebug>

#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>


MartletProject* MartletProject::m_instance = 0;


MartletProject::MartletProject()
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
    if (executable.empty()) return false;
    if (fileName.empty()) return false;
    if (type.empty()) return false;
    return true;
}

void MartletProject::loadFromFile(const  std::string& str )
{
    Q_ASSERT(!str.empty());
    fileName = str;

    std::ifstream ifs(fileName.c_str() /*, std::ios::in | std::ios::trunc*/);
    if (ifs.is_open()) {
        boost::archive::xml_iarchive xml(ifs);
        xml.register_type(static_cast<MartletProject*>(0));
//        MartletProject* pro = new MartletProject();
        xml >> boost::serialization::make_nvp("MartletProject", *this);
//        MartletProject::setCurrent(pro);
    }
}

void MartletProject::saveToFile(const  std::string& str)
{
    Q_ASSERT(!str.empty());
    fileName = str;

    std::ofstream ofs(fileName.c_str(), std::ios::out | std::ios::trunc);
    if (ofs.is_open()) {
        boost::archive::xml_oarchive xml(ofs);
        xml.register_type(static_cast<MartletProject*>(0));
        xml << boost::serialization::make_nvp("MartletProject", *this);
    }
}

void MartletProject::save()
{
    qDebug() << "Saving project to file "<< QString::fromStdString(fileName)<< " with contents:\n";
    saveToFile(fileName);
}


template<class archive>
void MartletProject::serialize(archive& ar, const unsigned int /*version*/)
{
    using boost::serialization::make_nvp;
    ar & make_nvp("Type", type);
    //ar & make_nvp("Filename", filename);
    ar & make_nvp("Executable", executable);
    ar & make_nvp("Suites", suites);
}

void MartletProject::notifyAboutChanges(int suiteIdx)
{
    emit projectChanged(suiteIdx);
}








//// SUITE









MartletProject::Suite::Suite(const std::string& nm, const std::string& fl)
{
    name = nm;
    file = fl;
}


template<class archive>
void MartletProject::Suite::serialize(archive& ar, const unsigned int /*version*/)
{
    using boost::serialization::make_nvp;
    ar & make_nvp("Name", name);
    ar & make_nvp("File", file);
}








