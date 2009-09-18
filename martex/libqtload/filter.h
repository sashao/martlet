#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QWidget>

#include <QKeyEvent>

#include <windows.h> 
__declspec( dllexport ) void Proc();
LRESULT __declspec(dllexport) CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

class filter : public QObject
{
	Q_OBJECT

public:
	filter();

signals:
	void objChanged(QObject * obj);

protected:
	bool eventFilter(QObject *obj, QEvent *event);

};


#endif // FILTER_H
