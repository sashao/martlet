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
    
    setState<InitState>();
    
    m_Model = new MProjectModel(this);
    m_Model->setProject(MartletProject::getCurrent());
    ui->treeView->setModel(m_Model);

    m_client = new MartletClient;
    connect(m_client, SIGNAL(recordedTextArrived(QString)), this, SLOT(onRecordedTextUpdate(QString)));
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
        on_actionRecord_triggered();
    } else {
        on_actionStop_recording_triggered();
    }
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
    bool ok = false;
    QString name = QInputDialog::getText(this, "SuiteName", "Enter new suite name:", QLineEdit::Normal, "xSuite", &ok);
    if (!name.isEmpty() && ok) {

        QString fname = QInputDialog::getText(this, "SuiteFileName", "Enter new suite file name:", QLineEdit::Normal, name+".qs", &ok);
        if (!fname.isEmpty() && ok) {
            MartletProject::Suite suite;
            suite.name = name.toStdString();
            suite.file = fname.toStdString();
            MartletProject::getCurrent()->suites.push_back(suite);
            MartletProject::getCurrent()->notifyAboutChanges(MartletProject::getCurrent()->suites.size());
        }
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

    bool ok = false;
    QString name = QInputDialog::getItem(this, "Delete suite", "Choose one", sl, -1, false, &ok);
    if (!name.isEmpty() && ok) {
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

void MartletWindow::on_actionStart_program_triggered()
{
    m_client->tryConnect();
}

void MartletWindow::on_actionRecord_triggered()
{
    Q_ASSERT(MartletProject::getCurrent() != NULL);
    startApp();
}

void MartletWindow::startApp()
{
    Q_ASSERT(MartletProject::getCurrent() != NULL);
    const QString app = QString("./martex.sh ") + QString::fromStdString(MartletProject::getCurrent()->executable);
    Q_ASSERT( !app.isEmpty() );
    qDebug("Starting App.");
    m_childAppProcess.start(app);
    QTimer::singleShot(4000, this, SLOT(tryConnectAndStart()));
}

void MartletWindow::tryConnectAndStart()
{
    if (!m_client->tryConnect()) {
        QTimer::singleShot(40000, this, SLOT(tryConnectAndStart()));
    } else {
        m_client->startRecording("f.qs");
    }
}


void MartletWindow::on_actionStop_recording_triggered()
{
    m_client->stopRecording("f.qs");
    m_client->askForRecordedText("f.qs");
    ui->plainTextEdit->setPlainText("\nWaitinng for text from client ....");
}

void MartletWindow::on_actionPlay_triggered()
{
    m_client->uploadScript("H.qs", ui->plainTextEdit->toPlainText());
    m_client->play("H.qs");
}

void MartletWindow::on_pushButton_4_clicked() // play
{
    on_actionPlay_triggered();
}

void MartletWindow::onRecordedTextUpdate(QString txt)
{
    qDebug() << "Text arrived to main window" << txt;
    ui->plainTextEdit->setPlainText( txt );

    const QString fname = QString::fromStdString( MartletProject::getCurrent()->currentSuite().file );
    QFile file(fname);
    file.open(QFile::WriteOnly|QFile::Text|QFile::Truncate);
    file.write(txt.toLocal8Bit());
    file.close();
}
