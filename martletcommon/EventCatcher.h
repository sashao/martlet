#ifndef EVENTCATCHER_H
#define EVENTCATCHER_H

#include <QObject>

class EventCatcher : public QObject
{
	Q_OBJECT

public:
	EventCatcher(QObject *parent);
	~EventCatcher();

	void startRecording();
	void stopRecording();

        void (*m_spy)(QObject *);


private:
	bool eventFilter(QObject *obj, QEvent *ev);	
};

#endif // EVENTCATCHER_H
