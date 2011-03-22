#include "CutterMainWindow.h"
#include "ui_CutterMainWindow.h"
#include <QFileDialog>

CutterMainWindow::CutterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CutterMainWindow)
{
    ui->setupUi(this);
    
}

CutterMainWindow::~CutterMainWindow()
{
    delete ui;
}

void CutterMainWindow::changeEvent(QEvent *e)
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

void CutterMainWindow::on_actionOpen_triggered()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image File"),
                                                   QDir::currentPath(),
                                                 tr("Images (*.png *.xpm *.jpg)")); 
   ui->imageWidget->setPixmap(fileName);
}

void CutterMainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save selected image as file"),
                            QDir::currentPath()+ "/untitled.png",
                            tr("Images (*.png *.xpm *.jpg)"));
   
   ui->imageWidget->savePixmap(fileName);
}

void CutterMainWindow::on_actionAuto_select_triggered()
{
   ui->imageWidget->autoSelect();
}
