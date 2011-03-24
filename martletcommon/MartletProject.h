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


#ifndef MARTLETPROJECT_H
#define MARTLETPROJECT_H

#include <QObject>
#include <QPixmap>
#include <QDir>

#include <vector>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>

class __declspec(dllexport) TestItem: public QObject
{
    Q_OBJECT
private:
protected:
    std::string m_name;
    int m_page;
    QPixmap m_icon;
    QString m_toolTip;

public:
    __declspec(dllexport) TestItem(TestItem * parent = 0);

    __declspec(dllexport) TestItem *parentItem() const
    {
        return qobject_cast<TestItem *> (parent());
    }
    __declspec(dllexport) bool hasParent() const
    {
        return parentItem() != 0;
    }

    __declspec(dllexport) bool hasChildren() const
    {
        return !childrenItems().isEmpty();
    }

    __declspec(dllexport) QList<TestItem *> childrenItems() const
    {
        QList<TestItem *> l;
        const QObjectList & objs = children();
        QObject* o = 0;
        foreach (o, objs) {
            TestItem * ti = qobject_cast<TestItem *>(o);
            if (ti) l.push_back(ti);
        }

        return l;
    }

    __declspec(dllexport) virtual std::string name() const
    {
        return m_name;
    }
    __declspec(dllexport) virtual void setName(const std::string &name)
    {
        m_name = name;
    }

    __declspec(dllexport) int page() const;
    __declspec(dllexport) QPixmap icon() const;
    __declspec(dllexport) QString toolTip() const;

    friend class MartletProject;

};


class __declspec(dllexport) TestFile : public TestItem
{
        Q_OBJECT
    public:
        __declspec(dllexport) TestFile(TestItem *parent, const QString& name);

    protected:
        TestFile();
        friend class boost::serialization::access;
        template<class archive>
        void serialize(archive& ar, const unsigned int /*version*/);

};




class __declspec(dllexport) TestCase : public TestItem
{
        Q_OBJECT
    public:
        __declspec(dllexport) TestCase(TestItem *parent, const QString& name);

        std::vector<TestFile *> files;

    protected:
        TestCase();
        friend class boost::serialization::access;
        template<class archive>
        void serialize(archive& ar, const unsigned int /*version*/);

};




class __declspec(dllexport) Suite : public TestItem
{
    Q_OBJECT
public:

    __declspec(dllexport) Suite(TestItem *parent=0, const std::string& nm = std::string());
    __declspec(dllexport) ~Suite();

//    /// suite name
//    std::string name;

    std::vector <TestCase *> testCases;

private:
    friend class boost::serialization::access;
    template<class archive>
    void serialize(archive& ar, const unsigned int /*version*/);
};




class __declspec(dllexport) MartletProject : public TestItem
{
    Q_OBJECT
public:

    __declspec(dllexport) MartletProject();
    __declspec(dllexport) virtual ~MartletProject();
    
    __declspec(dllexport) static MartletProject* getCurrent();
    __declspec(dllexport) static void setCurrent(MartletProject* pro);
    __declspec(dllexport) Suite* currentSuite() const;
    __declspec(dllexport) QDir projectDir() const;

    bool isValid() const;
    void loadFromFile(const  std::string& str );
    void saveToFile(const  std::string& str);
    /// saves to @ref fileName
    void save();
    
    /// Indicates that some changes where made after this project was loaded/saved/created.
    inline bool isDirty() const {
        /// TODO: compare with dom document.
        return m_isDirty;
    }

    TestItem *parent()
    {
        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    ////                      OPEN SECTION
    /////////////////////////////////////////////////////////////////////////////////////
    
    /// absolute path to tested executable with parameters.
    TestItem executable;
    /// Non empty list of available suites;
    std::vector<Suite *> suites;
    /**
     * Type string for decoding e.g. "mt-qscript"
     * Must be unique.
     */
    TestItem type;

    TestItem fileName;


    // SERIALIZATION
    friend class boost::serialization::access;
    template<class archive>
    void serialize(archive& ar, const unsigned int /*version*/);

    /// Break Encapsulation Pagadigm
    void notifyAboutChanges(int suiteIdx);
signals:
    void projectChanged(int suiteIdx);

protected:    
    bool m_isDirty;
    
    static MartletProject* m_instance;
};

#endif // MARTLETPROJECT_H
