#ifndef EVENTSENDER_H
#define EVENTSENDER_H

#include <QtGui/QMainWindow>
#include "ui_eventsender.h"
#include "EventCatcher.h"

class eventsender : public QMainWindow
{
	Q_OBJECT

public:
	eventsender(QWidget *parent = 0, Qt::WFlags flags = 0);
	~eventsender();

private:
	Ui::eventsenderClass ui;
	EventCatcher catcher;

private slots:
    void on_playBtn_clicked();
    void on_groupBox_toggled(bool);
	void on_pushButton_3_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_clicked();
	void on_checkBox_clicked(bool);
};

#endif // EVENTSENDER_H
