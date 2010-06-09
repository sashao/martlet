#ifndef MARTLETPROJECT_H
#define MARTLETPROJECT_H

#include <QObject>
#include <QFile>
#include <QDomElement>
#include <QDomDocument>

class MartletProject : public QObject
{
    Q_OBJECT
public:

    class Suite
    {
    public:
        Suite(const QString& nm = QString(), const QString& fl = QString());
        void load(const  QDomElement& root);
        void save(QDomDocument& doc) const;
        /// suite name
        QString name;
        /// file to load
        QString file;
    };

    MartletProject();
    virtual ~MartletProject();
    
    static MartletProject* getCurrent();
    static void setCurrent(MartletProject* pro);
    
    bool isValid();
    void loadFromFile(const  QString& str );
    void saveToFile(const  QString& str);
    /// saves to xml and to file all Suites and project settings
    void save();
    /// loads from xml all Suites and project settings
    void load();
    /// project nodes
    void saveSettings();
    void loadSettings();
    
    /// Indicates that some changes where made after this project was loaded/saved/created.
    inline bool isDirty() const {
        /// TODO: compare with dom document.
        return m_isDirty;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    ////                      OPEN SECTION
    /////////////////////////////////////////////////////////////////////////////////////
    
    /// absolute path to tested executable with parameters.
    QString executable;
    /// Non empty list of available suites;
    QList<Suite> suites;
    /**
     * Type string for decoding e.g. "mt-qscript"
     * Must be unique.
     */
    QString type; 

    QString fileName;

protected:    
    bool m_isDirty;
    QDomDocument m_doc;
    
    static MartletProject* m_instance;
};

#endif // MARTLETPROJECT_H
