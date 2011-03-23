//    Martlet - application automated Qt GUI application testing and more.
//    Copyright (C) 2010  Oleksandr Omelchuk sashao@e-mail.ua

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QWidget>

#include <QKeyEvent>

//#include <windows.h> 
//__declspec( dllexport ) void Proc();
//LRESULT __declspec(dllexport) CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

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
