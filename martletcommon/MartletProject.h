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

class TestItem: public QObject
{
    Q_OBJECT
private:
protected:
    std::string m_name;
    int m_page;
    QPixmap m_icon;
    QString m_toolTip;

public:
    TestItem(TestItem * parent = 0);

    TestItem *parentItem() const
    {
        return qobject_cast<TestItem *> (parent());
    }
    bool hasParent() const
    {
        return parentItem() != 0;
    }

    bool hasChildren() const
    {
        return !childrenItems().isEmpty();
    }
    QList<TestItem *> childrenItems() const
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

    virtual std::string name() const
    {
        return m_name;
    }
    virtual void setName(const std::string &name)
    {
        m_name = name;
    }

    int page() const;
    QPixmap icon() const;
    QString toolTip() const;

    friend class MartletProject;

};


class TestFile : public TestItem
{
        Q_OBJECT
    public:
        TestFile(TestItem *parent, const QString& name);

    protected:
        TestFile();
        friend class boost::serialization::access;
        template<class archive>
        void serialize(archive& ar, const unsigned int /*version*/);

};




class TestCase : public TestItem
{
        Q_OBJECT
    public:
        TestCase(TestItem *parent, const QString& name);

        std::vector<TestFile *> files;

    protected:
        TestCase();
        friend class boost::serialization::access;
        template<class archive>
        void serialize(archive& ar, const unsigned int /*version*/);

};




class Suite : public TestItem
{
    Q_OBJECT
public:

    Suite(TestItem *parent=0, const std::string& nm = std::string());
    ~Suite();

//    /// suite name
//    std::string name;

    std::vector <TestCase *> testCases;

private:
    friend class boost::serialization::access;
    template<class archive>
    void serialize(archive& ar, const unsigned int /*version*/);
};




class MartletProject : public TestItem
{
    Q_OBJECT
public:

    MartletProject();
    virtual ~MartletProject();
    
    static MartletProject* getCurrent();
    static void setCurrent(MartletProject* pro);
    Suite* currentSuite() const;
    QDir projectDir() const;

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
