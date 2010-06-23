#ifndef MARTLETPROJECT_H
#define MARTLETPROJECT_H

#include <QObject>

#include <vector>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>

class MartletProject  : public QObject
{
    Q_OBJECT
public:

    class Suite
    {
    public:
        Suite(const std::string& nm = std::string(), const std::string& fl = std::string());
        /// suite name
        std::string name;
        /// file to load
        std::string file;

        friend class boost::serialization::access;
        template<class archive>
        void serialize(archive& ar, const unsigned int /*version*/);
    };

    MartletProject();
    virtual ~MartletProject();
    
    static MartletProject* getCurrent();
    static void setCurrent(MartletProject* pro);
    
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

    /////////////////////////////////////////////////////////////////////////////////////
    ////                      OPEN SECTION
    /////////////////////////////////////////////////////////////////////////////////////
    
    /// absolute path to tested executable with parameters.
    std::string executable;
    /// Non empty list of available suites;
    std::vector<Suite> suites;
    /**
     * Type string for decoding e.g. "mt-qscript"
     * Must be unique.
     */
    std::string type;

    std::string fileName;


    // SERIALIZATION
    friend class boost::serialization::access;
    template<class archive>
    void serialize(archive& ar, const unsigned int /*version*/);

protected:    
    bool m_isDirty;
    
    static MartletProject* m_instance;
};

#endif // MARTLETPROJECT_H
