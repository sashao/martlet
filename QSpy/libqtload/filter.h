#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QWidget>

#include <QKeyEvent>

class filter : public QObject
{
   Q_OBJECT
public:
    filter(){ w = 0;}
QWidget* w;
protected:
bool eventFilter(QObject *obj, QEvent *event);
};
//class filter : public QObject
//{
//public:
//    filter();
//};

#endif // FILTER_H
