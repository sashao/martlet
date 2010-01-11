#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H

#include <QObject>
#include <QEvent>
#include <QTime>
/**
 *  Data needed to record and play single event basic params
 */
class CommandData 
{
public:
    CommandData();
    CommandData(QEvent* event, const QString& nameString, const unsigned int pause);
    bool isValid() const;

    unsigned int pause_msecs;
    QEvent* event;
    QString objNameString;
};

class AbstractCommand : public QObject
{
	Q_OBJECT

public:
	AbstractCommand(QObject *parent);
	~AbstractCommand();

	/// Return true if this instance can be deserialized from this string.
	virtual bool canDeserialize(const QString commanStr) = 0;
	
	virtual QString record(const CommandData& data) = 0;
	/// Returns True if success.
	virtual bool exec() = 0;

	virtual CommandData deserialize(const QString commanStr) = 0;
	
	virtual QEvent::Type type() = 0;

    static void clearTimers();
    static unsigned int getPauseMSecs();
    
    static void recordLastEventTime();

protected:
    static QTime m_lastEventTime;
    static QTime m_mouseMoveTime;
    static QTime m_mousePressTime;
    static QTime m_mouseReleaseTime;
};




#endif // ABSTRACTCOMMAND_H
