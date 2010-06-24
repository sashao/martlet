#include "MartletWindow.h"
#include "ui_MartletWindow.h"
#include "CSVEventFabric.h"
#include "MartletProject.h"
#include "AppSettingsDialog.h"
#include "ProjectDialog.h"
#include "MProjectModel.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>







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
    if (MartletProject::getCurrent())
    {
        if (QMessageBox::Yes ==   QMessageBox::question(this, "Save ?", 
                                  "Do you want to save previous project ?", 
                                  QMessageBox::Yes, QMessageBox::No)) 
        {
            MartletProject::getCurrent()->save();
        }
    }

    const QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Select New project file"), AppSettingsDialog::currentDir() , 
                                                    tr("Martlet Project Files (*.mtproject *.mtp)"));
    if (!fileName.isEmpty()) {

        m_Model->setProject(0);
        delete MartletProject::getCurrent();
        MartletProject::setCurrent(0);
        
        MartletProject* pro = new MartletProject(); 
        MartletProject::setCurrent(pro);
        pro->fileName = fileName.toStdString();
        
        ProjectDialog pdialog(this);
        pdialog.setProject(pro);
        pdialog.exec();
         
        if (pdialog.result() == QDialog::Accepted)
        {
            MartletProject::Suite suite1("TestSuite1", "TestSuite1.qs");
            pro->suites.push_back(suite1);
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
    // TODO
}

void MartletWindow::on_actionOpen_triggered()
{
}

void MartletWindow::on_actionSave_2_triggered()
{
    if (MartletProject::getCurrent()) {
        MartletProject::getCurrent()->save(); 
    }     
}

void MartletWindow::on_actionSave_As_triggered()
{
    //TODO
}

void MartletWindow::on_actionLoad_triggered()
{
    if (MartletProject::getCurrent())
    {
        if (QMessageBox::Yes ==   QMessageBox::question(this, "Save ?", 
                                  "Do you want to save previous project ?", 
                                  QMessageBox::Yes, QMessageBox::No)) 
        {
            MartletProject::getCurrent()->save();
        }
    }
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("Select project file to open"), AppSettingsDialog::currentDir() ,
                       tr("Martlet Project Files (*.mtproject *.mtp)"));

    if (!fileName.isEmpty()) {
        m_Model->setProject(0);
        delete MartletProject::getCurrent();    
        MartletProject::setCurrent(0);
        
        MartletProject* pro = new MartletProject(); 
        // load project
        pro->loadFromFile(fileName.toStdString());
        MartletProject::setCurrent(pro);

        loadCurrentProjectIntoUI();
        setState<ProjectOpenedState>();
    }    
}

void MartletWindow::on_actionNew_Suite_triggered()
{
    QString name = QInputDialog::getText(this, "SuiteName", "Enter new suite name:", QLineEdit::Normal, "xSuite");
    if (!name.isEmpty()) {
        MartletProject::Suite suite;
        suite.name = name.toStdString();
        MartletProject::getCurrent()->suites.push_back(suite);
        MartletProject::getCurrent()->notifyAboutChanges(MartletProject::getCurrent()->suites.size());
    }
}

void MartletWindow::on_actionDelete_existing_suite_triggered()
{
    QStringList sl;

    std::vector<MartletProject::Suite>& suites = MartletProject::getCurrent()->suites;

    std::vector<MartletProject::Suite>::iterator iter = suites.begin();
    for (;iter !=  suites.end(); ++iter) {
        sl.append( QString::fromStdString((*iter).name) );
    }

    QString name = QInputDialog::getItem(this, "Delete suite", "Choose one", sl);
    if (!name.isEmpty()) {
        std::vector<MartletProject::Suite>::iterator iter = suites.begin();
        for (;iter != suites.end(); ++iter) {
            if (QString::fromStdString((*iter).name)  == name) {
                suites.erase(iter);
                break;
            }
        }
        MartletProject::getCurrent()->notifyAboutChanges(MartletProject::getCurrent()->suites.size());
    }

}
