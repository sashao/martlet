#include "MartletWindow.h"
#include "ui_MartletWindow.h"
#include "CSVEventFabric.h"


MartletWindow::MartletWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MartletWindow)
{
    ui->setupUi(this);
    AbstractEventFabric::setInstance(new CSVEventFabric(this));
}

MartletWindow::~MartletWindow()
{
    delete ui;
}

void MartletWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MartletWindow::on_pushButton_3_toggled(bool checked)
{
    if (checked) {
        m_client->startRecording();
    } else {
        m_client->stopRecording();
    }
}

void MartletWindow::on_pushButton_4_clicked()
{
    // play
    m_client->uploadScript("main.csv", ui->plainTextEdit->toPlainText());
    m_client->play("main.csv");
}

void MartletWindow::on_pushButton_clicked()
{
    // start server
    
    m_server = new MartletServer;

    m_client = new MartletClient;

}
