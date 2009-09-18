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


class QSpyWidget : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(QSpyWidget)

	explicit QSpyWidget(QWidget *parent = 0);
    virtual ~QSpyWidget();

public:
	static QSpyWidget *instance();

public slots:
	void setObject(QObject * obj);

protected:
	void createActions();
	void createTrayIcon();
	void setVisible(bool visible);

    virtual void changeEvent(QEvent *e);
	bool updateObjectTree(QObject * obj);
	void addChildrens(QTreeWidgetItem *parent, QObject * obj);
	void closeEvent(QCloseEvent *event);

private:
	static QSpyWidget * m_instance;
	Ui::QSpyForm *m_ui;
	QObject *selected;
	QObject *m_top;

	QDesignerObjectInspectorInterface *oi;
	QDesignerPropertyEditorInterface *pe;
	QDesignerFormEditorInterface *m_formeditor;

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
