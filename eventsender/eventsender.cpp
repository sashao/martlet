#include "eventsender.h"
#include "AbstractEventFabric.h"

#include <QApplication>
#include <QMouseEvent>
#include <QKeyEvent>

eventsender::eventsender(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),
	catcher(this)
{
	ui.setupUi(this);
}

eventsender::~eventsender()
{

}


void eventsender::on_checkBox_clicked(bool)
{
	qDebug("eventsender::on_checkBox_clicked(bool)");
}

void eventsender::on_pushButton_clicked()
{
	qDebug("eventsender::on_pushButton_clicked()");
	QMouseEvent* me = new QMouseEvent(QEvent::MouseButtonPress,QPoint(5,5), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QApplication::sendEvent(ui.checkBox, me);
	QMouseEvent* me2 = new QMouseEvent(QEvent::MouseButtonRelease,QPoint(5,5), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QApplication::sendEvent(ui.checkBox, me2);
}

void eventsender::on_pushButton_2_clicked()
{
	catcher.startRecording();
}

void eventsender::on_pushButton_3_clicked()
{
	catcher.stopRecording();
    ui.textBrowser->setText(AbstractEventFabric::instance()->getOutput());
}

void eventsender::on_groupBox_toggled(bool)
{

}

void eventsender::on_playBtn_clicked()
{
    QStringList lines = ui.textBrowser->toPlainText().split("\n", QString::SkipEmptyParts);
    QString line;
    foreach (line, lines)
    {
        AbstractEventFabric::instance()->playSingleLineEvent(line);
    }
}

void eventsender::on_comboBox_textChanged(const QString &)
{

}