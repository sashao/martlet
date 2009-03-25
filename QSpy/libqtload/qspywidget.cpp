#include "qspywidget.h"
#include "ui_qspywidget.h"

//#include "designerconstants.h"
//#include "objectinspector.h"

//#include <QtDesigner>
//#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerComponents>
#include <QtDesigner/abstractobjectinspector.h>
#include <QtDesigner/QDesignerPropertyEditorInterface>
#include <QtDesigner/QDesignerObjectInspectorInterface>


QSpyWidget * QSpyWidget::m_instance = 0;


QSpyWidget::QSpyWidget(QWidget *parent) :
    QWidget(parent),
	m_ui(new Ui::QSpyForm)
{
	selected = 0;
    m_ui->setupUi(this);

	m_formeditor = QDesignerComponents::createFormEditor(0);

//	oi = QDesignerComponents::createObjectInspector(m_formeditor, 0);
//	oi->setWindowTitle(tr("Object inspector"));

//	QDesignerObjectInspector *oi2 = qobject_cast<QDesignerObjectInspector *>(oi);

	pe = QDesignerComponents::createPropertyEditor(m_formeditor, 0);
	pe->setWindowTitle(tr("Property editor"));
//	m_ui->splitter->addWidget(oi);
	m_ui->splitter->addWidget(pe);

//	pe->setObject(oi);
}

QSpyWidget *QSpyWidget::instance()
{
	if (!m_instance)
	{
		m_instance = new QSpyWidget();
	}
	return m_instance;
}


void QSpyWidget::setObject(QObject * obj)
{
	if (obj) selected = obj;
	else return;

	if (updateObjectTree(obj))
		pe->setObject(obj);
}

bool QSpyWidget::updateObjectTree(QObject * obj)
{
	if (obj && obj->isWidgetType())
	{
		QWidget* w = qobject_cast<QWidget *>(obj);
		QWidget* tw  = w->topLevelWidget();
		if (tw == this) return false;

		m_ui->treeWidget->clear();

		QTreeWidgetItem *objItem = new QTreeWidgetItem(m_ui->treeWidget);
		objItem->setText(1, tw->objectName());
		objItem->setText(0, tw->metaObject()->className());
		m_ui->treeWidget->addTopLevelItem(objItem);

		addChildrens(objItem, tw);

		m_ui->treeWidget->expandAll();
		return true;
	}
	return false;
}


void QSpyWidget::addChildrens(QTreeWidgetItem *parent, QObject * obj)
{
	QObjectList childs = obj->children();
	QObject *child = 0;
	foreach (child, childs)
	{
		QTreeWidgetItem *objItem = new QTreeWidgetItem(parent);
		objItem->setText(1, child->objectName());
		objItem->setText(0, child->metaObject()->className());
		objItem->setData(0, Qt::UserRole, QVariant::fromValue(child));
		if (child == selected)
			objItem->setSelected(true);

		addChildrens(objItem, child);
	}
}


QSpyWidget::~QSpyWidget()
{
    delete m_ui;
}

void QSpyWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
