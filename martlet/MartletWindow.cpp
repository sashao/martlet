#include "MartletWindow.h"
#include "ui_MartletWindow.h"
#include "CSVEventFabric.h"
#include "MartletProject.h"
#include "AppSettingsDialog.h"
#include "ProjectDialog.h"
#include "MProjectModel.h"

#include <QFileDialog>







MartletWindow::MartletWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MartletWindow)
{
    ui->setupUi(this);
    AbstractEventFabric::setInstance(new CSVEventFabric(this));
    
    setState<InitState>();
    
    m_Model = new MProjectModel(this);
    m_Model->setProject(MartletProject::getCurrent());
    ui->treeView->setModel(m_Model);
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

void MartletWindow::on_actionNew_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Select New project file"), AppSettingsDialog::currentDir() , 
                                                    tr("Martlet Project Files (*.mtproject *.mtp)"));
    if (!fileName.isEmpty()) {
        // TODO save
        if (MartletProject::getCurrent())
        {
            MartletProject::getCurrent()->save();
        }
        
        delete MartletProject::getCurrent();
        
        MartletProject* pro = new MartletProject(); 
        MartletProject::setCurrent(pro);
        pro->fileName = fileName;
        
        ProjectDialog pdialog(this);
        pdialog.setProject(pro);
        pdialog.exec();
         
        if (pdialog.result() == QDialog::Accepted)
        {
            MartletProject::Suite suite1("TestSuite1", "TestSuite1.qs");
            pro->suites<< suite1;
            MartletProject::Suite suite2("TestSuite2", "TestSuite2.qs");
            pro->suites<< suite2;
            pro->save();
            // load project
            loadCurrentProjectIntoUI();
            setState<ProjectOpenedState>();
        }
    }
}

void MartletWindow::loadCurrentProjectIntoUI()
{
    m_Model->setProject(MartletProject::getCurrent());    
}


void MartletWindow::on_actionSave_triggered()
{
    
}

void MartletWindow::on_actionOpen_triggered()
{
    
}
