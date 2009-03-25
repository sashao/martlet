#ifndef QSPYWIDGET_H
#define QSPYWIDGET_H

#include <QtGui/QWidget>

namespace Ui {
	class QSpyForm;
}

class QTreeWidgetItem;
class QDesignerPropertyEditorInterface;
class QDesignerFormEditorInterface;
class QDesignerObjectInspectorInterface;

class QSpyWidget : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(QSpyWidget)

	explicit QSpyWidget(QWidget *parent = 0);
    virtual ~QSpyWidget();

public:
	static QSpyWidget *instance();
	void setObject(QObject * obj);

protected:
    virtual void changeEvent(QEvent *e);
	bool updateObjectTree(QObject * obj);
	void addChildrens(QTreeWidgetItem *parent, QObject * obj);

private:
	static QSpyWidget * m_instance;
	Ui::QSpyForm *m_ui;
	QObject *selected;

	QDesignerObjectInspectorInterface *oi;
	QDesignerPropertyEditorInterface *pe;
	QDesignerFormEditorInterface *m_formeditor;
};

#endif // QSPYWIDGET_H
