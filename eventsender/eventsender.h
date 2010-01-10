#ifndef EVENTSENDER_H
#define EVENTSENDER_H

#include <QtGui/QMainWindow>
#include "ui_eventsender.h"

class eventsender : public QMainWindow
{
	Q_OBJECT

public:
	eventsender(QWidget *parent = 0, Qt::WFlags flags = 0);
	~eventsender();

private:
	Ui::eventsenderClass ui;

private slots:
	void on_pushButton_clicked();
	void on_checkBox_clicked(bool);
};

#endif // EVENTSENDER_H
