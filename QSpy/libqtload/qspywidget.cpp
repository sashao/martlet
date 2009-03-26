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

#include <QMenu>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>


QSpyWidget * QSpyWidget::m_instance = 0;


QSpyWidget::QSpyWidget(QWidget *parent) :
    QWidget(parent),
	m_ui(new Ui::QSpyForm)
{
	selected = 0;
	m_top = 0;
	m_ui->setupUi(this);
	m_ui->treeWidget->setColumnWidth(0, 220);

	m_formeditor = QDesignerComponents::createFormEditor(0);

//	oi = QDesignerComponents::createObjectInspector(m_formeditor, 0);
//	oi->setWindowTitle(tr("Object inspector"));

//	QDesignerObjectInspector *oi2 = qobject_cast<QDesignerObjectInspector *>(oi);

	pe = QDesignerComponents::createPropertyEditor(m_formeditor, 0);
	pe->setWindowTitle(tr("Property editor"));
//	m_ui->splitter->addWidget(oi);
	m_ui->splitter->addWidget(pe);

//	pe->setObject(oi);

	createActions();
	createTrayIcon();

//	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
//	    this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	connect(pe, SIGNAL(propertyChanged(const QString &, const QVariant &)),
			this, SLOT(handle_propertyChanged(const QString &, const QVariant &)));

	trayIcon->show();
	this->show();
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
		m_top = w->topLevelWidget();
		if (m_top == this) return false;

		m_ui->treeWidget->clear();

		QTreeWidgetItem *objItem = new QTreeWidgetItem(m_ui->treeWidget);
		objItem->setText(1, m_top->objectName());
		objItem->setText(0, m_top->metaObject()->className());
		m_ui->treeWidget->addTopLevelItem(objItem);

		addChildrens(objItem, m_top);

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
		objItem->setData(0, Qt::UserRole, qVariantFromValue((void *) child));
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

void QSpyWidget::closeEvent(QCloseEvent *event)
{
	hide();
	event->ignore();
}

// + system tray

void QSpyWidget::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    minimizeAction->setEnabled(isVisible());

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void QSpyWidget::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon("./images/bad.svg"));
}

void QSpyWidget::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    restoreAction->setEnabled(!visible);
    QWidget::setVisible(visible);
}

// - system tray

void QSpyWidget::on_treeWidget_itemActivated(QTreeWidgetItem* /*item*/, int /*column*/)
{
}

void QSpyWidget::on_treeWidget_itemClicked(QTreeWidgetItem* item, int /*column*/)
{
	QVariant varObj = item->data(0, Qt::UserRole);
	if ( varObj.isValid() /*&& (varObj.type() == QMetaType::QObjectStar)*/)
	{
		QObject * obj = (QObject *) varObj.value<void *>();
		//	qWarning("TODO: %s:%d", __FILE__, __LINE__);
		//	qDebug()<< varObj << item->data(0, Qt::EditRole) << "    "<< long(obj);
		if (obj)
		{
			pe->setObject(obj);
			selected = obj;
		}
	}
}

void QSpyWidget::handle_propertyChanged ( const QString & name, const QVariant & value )
{
	qWarning("TODO: %s:%d", __FILE__, __LINE__);
	pe->object()->setProperty(name.toLocal8Bit(), value);
}

