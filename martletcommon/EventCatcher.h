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

        void blockSpontaneousEvents(const bool block);

private:
	bool eventFilter(QObject *obj, QEvent *ev);	
        bool m_blockSpontaneous;
};

#endif // EVENTCATCHER_H
