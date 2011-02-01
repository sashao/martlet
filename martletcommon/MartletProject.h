#ifndef MARTLETPROJECT_H
#define MARTLETPROJECT_H

#include <QObject>

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
};

class TestCase : public TestItem
{
        Q_OBJECT
    public:
        TestCase(TestItem *parent, const QString& name);

//        /// suite name
//        std::string name;
//        /// file to load
//        std::string file;

    protected:
        TestCase();
        friend class boost::serialization::access;
        template<class archive>
        void serialize(archive& ar, const unsigned int /*version*/);

};

class Suite : public TestItem
{
    Q_OBJECT
    explicit Suite(TestItem *parent);
public:

    Suite(TestItem *parent=0, const std::string& nm = std::string());
    ~Suite();

//    /// suite name
//    std::string name;

    std::vector <TestCase *> m_pTestCases;

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
    Suite* currentSuite();

    bool isValid();
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
    std::string executable;
    /// Non empty list of available suites;
    std::vector<Suite *> suites;
    /**
     * Type string for decoding e.g. "mt-qscript"
     * Must be unique.
     */
    std::string type;

    TestItem fileName;


    // SERIALIZATION
    friend class boost::serialization::access;
    template<class archive>
    void serialize(archive& ar, const unsigned int /*version*/);

    /// Break Object Oriented Pagadigm
    void notifyAboutChanges(int suiteIdx);
signals:
    void projectChanged(int suiteIdx);

protected:    
    bool m_isDirty;
    
    static MartletProject* m_instance;
};

#endif // MARTLETPROJECT_H
