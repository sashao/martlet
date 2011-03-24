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

#ifndef QSPYWIDGET_H
#define QSPYWIDGET_H


#include <QtGui/QWidget>
#include <QSystemTrayIcon>


namespace Ui {
	class QSpyForm;
}

class QTreeWidgetItem;
class QDesignerPropertyEditorInterface;
class QDesignerFormEditorInterface;
class QDesignerObjectInspectorInterface;
class QSystemTrayIcon;
class QMenu;
class QCloseEvent;


class  __declspec(dllexport) QSpyWidget : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(QSpyWidget)

    __declspec(dllexport) explicit QSpyWidget(QWidget *parent = 0);
    __declspec(dllexport) virtual ~QSpyWidget();

public:
        __declspec(dllexport) static QSpyWidget *instance();

public slots:
        void setObject(QObject * obj);

protected:
        __declspec(dllexport) void createActions();
        __declspec(dllexport) void createTrayIcon();
        __declspec(dllexport) void setVisible(bool visible);

        __declspec(dllexport) virtual void changeEvent(QEvent *e);
        __declspec(dllexport) bool updateObjectTree(QObject * obj);
        __declspec(dllexport) void addChildrens(QTreeWidgetItem *parent, QObject * obj);
        __declspec(dllexport) void closeEvent(QCloseEvent *event);

private:
	static QSpyWidget * m_instance;
	Ui::QSpyForm *m_ui;
	QObject *selected;
	QObject *m_top;

#ifndef Q_OS_WIN32
	QDesignerObjectInspectorInterface *oi;
	QDesignerPropertyEditorInterface *pe;
	QDesignerFormEditorInterface *m_formeditor;
#endif
	QSystemTrayIcon *trayIcon;
	QMenu *trayIconMenu;

	QAction *minimizeAction;
	QAction *restoreAction;
	QAction *quitAction;

private slots:
        void handle_propertyChanged ( const QString & name, const QVariant & value );
        void on_treeWidget_itemActivated(QTreeWidgetItem* item, int column);
        void on_treeWidget_itemClicked(QTreeWidgetItem* item, int column);

};

#endif // QSPYWIDGET_H
