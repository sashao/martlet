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
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->menuBar->removeAction(ui->menuContextMenu->menuAction());

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

template <class C>
C* MartletWindow::getCurrentItem()
{

    const QModelIndex i = ui->treeView->currentIndex();
    return qobject_cast<C *>(static_cast<TestItem *>(i.internalPointer()));
}


void MartletWindow::on_treeView_customContextMenuRequested ( const QPoint & pos )
{
    QList <QAction *> al;

    const QModelIndex i = ui->treeView->indexAt(pos);

    if (i.isValid()) {

        if ( getCurrentItem<TestFile>() ) {
            al = ui->menuTest_file->actions();
        } else
        if ( getCurrentItem<TestCase>() ) {
            al = ui->menuTestcase->actions();
        } else
        if ( getCurrentItem<Suite>() ) {
            al = ui->menuSuite->actions();
        } else
        if ( getCurrentItem<MartletProject>() ) {
            al = ui->menuProject_2->actions();
        }

        if (!al.isEmpty()) {
            QMenu::exec(al, ui->treeView->viewport()->mapToGlobal(pos));
        }
    }
}


void MartletWindow::on_treeView_clicked(QModelIndex index)
{
    const QModelIndex i = ui->treeView->currentIndex();

    if (i.isValid()) {

        if ( TestFile * tf = getCurrentItem<TestFile>() ) {

            const QString fname = QDir::currentPath()+QDir::separator()+ QString::fromStdString( tf->name() );
            qDebug("Loading file %s", qPrintable(fname));
            QFile file(fname);
            file.open(QFile::ReadOnly|QFile::Text|QFile::Truncate);
            QString txt = file.readAll();
            file.close();
            // load file
            ui->plainTextEdit->setPlainText( txt );

        } else
        if ( getCurrentItem<TestCase>() ) {
        } else
        if ( getCurrentItem<Suite>() ) {
        } else
        if ( getCurrentItem<MartletProject>() ) {
        }

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
        pro->fileName.setName(fileName.toStdString());
        QFileInfo i (fileName);
        pro->setName( i.baseName().toStdString());
        
        ProjectDialog pdialog(this);
        pdialog.setProject(pro);
        pdialog.exec();
         
        if (pdialog.result() == QDialog::Accepted)
        {
            Suite* suite1 = new Suite(pro, "TestSuite1");
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
    ui->treeView->expandAll();
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

//        QString fname = QInputDialog::getText(this, "SuiteFileName", "Enter new suite file name:", QLineEdit::Normal, name+".qs", &ok);
//        if (!fname.isEmpty() && ok) {
            Suite* suite = new Suite(MartletProject::getCurrent(), name.toStdString());
            MartletProject::getCurrent()->suites.push_back(suite);
            loadCurrentProjectIntoUI();
//        }
        }
}

void MartletWindow::on_actionDelete_existing_suite_triggered()
{
    QStringList sl;

    std::vector<Suite *>& suites = MartletProject::getCurrent()->suites;

    std::vector<Suite *>::iterator iter = suites.begin();
    for (;iter !=  suites.end(); ++iter) {
        sl.append( QString::fromStdString((*iter)->name()) );
    }

    bool ok = false;
    QString name = QInputDialog::getItem(this, "Delete suite", "Choose one", sl, -1, false, &ok);
    if (!name.isEmpty() && ok) {
        std::vector<Suite *>::iterator iter = suites.begin();
        for (;iter != suites.end(); ++iter) {
            if (QString::fromStdString((*iter)->name())  == name) {
                delete (* iter);
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
    const QString app = QString("./martex.sh ") + QString::fromStdString(MartletProject::getCurrent()->executable.name());
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

    const QString fname = QString::fromStdString( MartletProject::getCurrent()->currentSuite()->name() );
    QFile file(fname);
    file.open(QFile::WriteOnly|QFile::Text|QFile::Truncate);
    file.write(txt.toLocal8Bit());
    file.close();
}

void MartletWindow::on_actionProject_Add_suite_triggered()
{
    MartletProject * p = getCurrentItem<MartletProject>();
    if (p) {
        const QString n = QInputDialog::getText(this, "Enter suite name", "Suite name");
        if (!n.isEmpty())  {
            Suite *s = new Suite(p, n.toStdString());
            p->suites.push_back(s);
            loadCurrentProjectIntoUI();
        }
    }
}

void MartletWindow::on_actionSuite_Delete_triggered()
{
    Suite * s = getCurrentItem<Suite>();
    if (s) {
        std::vector<Suite *>::iterator i =
                std::find(MartletProject::getCurrent()->suites.begin(), MartletProject::getCurrent()->suites.end(), s);
        if (i != MartletProject::getCurrent()->suites.end()) {
            MartletProject::getCurrent()->suites.erase(i, i+1);
            delete s;
            loadCurrentProjectIntoUI();
        }
    }
}

void MartletWindow::on_actionSuite_Add_Test_Case_triggered()
{
    Suite * s = getCurrentItem<Suite>();
    if (s) {
        const QString n = QInputDialog::getText(this, "Enter test case name", "Test Case name");
        if (!n.isEmpty())  {
            s->testCases.push_back(new TestCase(s, n));
            loadCurrentProjectIntoUI();
        }
    }
}

void MartletWindow::on_actionTK_Delete_triggered()
{
    TestCase * tc = getCurrentItem<TestCase>();
    if (tc) {
        Suite * suite = qobject_cast<Suite *>(tc->parentItem());
        if (suite) {
            std::vector<TestCase *>::iterator i =
                    std::find( suite->testCases.begin(), suite->testCases.end(), tc);
            if (i != suite->testCases.end()) {
                suite->testCases.erase(i, i+1);
                delete tc;
                loadCurrentProjectIntoUI();
            }
        }
    }
}

void MartletWindow::on_actionTK_Add_File_triggered()
{
    TestCase * tk = getCurrentItem<TestCase>();
    if (tk) {
        const QString n = QInputDialog::getText(this, "Enter test file name", "Test File name");
        if (!n.isEmpty())  {
            tk->files.push_back(new TestFile(tk, n));
            loadCurrentProjectIntoUI();
        }
    }

}

void MartletWindow::on_actionRecord_from_scratch_triggered()
{

}

void MartletWindow::on_actionFile_Delete_From_Suite_triggered()
{

}

void MartletWindow::on_actionFile_Delete_Phisically_triggered()
{

}

