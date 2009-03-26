#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QWidget>

#include <QKeyEvent>

class filter : public QObject
{
	Q_OBJECT

public:
	filter();

protected:
	bool eventFilter(QObject *obj, QEvent *event);

};


#endif // FILTER_H
