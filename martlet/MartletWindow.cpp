//    Martlet - application automated Qt GUI application testing and more.
//    Copyright (C) 2010  Oleksandr Omelchuk sashao@e-mail.ua

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "MartletWindow.h"
#include "ui_MartletWindow.h"
#include "CSVEventFabric.h"
#include "MartletProject.h"
#include "AppSettingsDialog.h"
#include "ProjectDialog.h"
#include "MProjectModel.h"
#include "RequestToRemote.h"
#include "QObjectPropertyModel.h"
#include "MartletSettings.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QTimer>
#include <QDateTime>
#include <QScrollBar>
#include<QSignalMapper>





MartletWindow::MartletWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MartletWindow),
    m_mode_play(true),
    m_string_mapper( new QSignalMapper(this) )
{
    ui->setupUi(this);
    
    setState<InitState>();
    
    m_Model = new MProjectModel(this);
    m_Model->setProject(MartletProject::getCurrent());
    ui->treeView->setModel(m_Model);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->menuBar->removeAction(ui->menuContextMenu->menuAction());

    m_client = new MartletClient;
    connect(m_client, SIGNAL(recordedTextArrived(QVariant)), this, SLOT(onRecordedTextUpdate(QVariant)));
    m_client->client()->connectRemoteSignal(PLAYBACK_TEST_START_1,
                                            this, SLOT(onTestSrated(QVariant)));
    m_client->client()->connectRemoteSignal(PLAYBACK_TEST_DONE_2,
                                            this, SLOT(onTestDone(QVariant, QVariant)));
    m_client->client()->connectRemoteSignal(APP_DEBUG_2,
                                            this, SLOT(onDebug(QVariant,QVariant)));
    m_client->client()->connectRemoteSignal(PLAYBACK_FINISHED_0,
                                            this, SLOT(onPlaybackFinished()));
    qDebug("Connection before Playing script ... ");
    connect(m_client->client(), SIGNAL(connected()),
            this, SLOT(onTestedAppConnected()));
    connect(ui->plainTextEdit, SIGNAL(modificationChanged(bool)), ui->plainTextEdit->document(), SLOT(setModified(bool)));
    connect(ui->plainTextEdit, SIGNAL(modificationChanged(bool)), ui->actionSave, SLOT(setEnabled(bool)));
    ui->actionSave->setEnabled(false);

#ifdef TEST_PROPERTY_MODEL
    QObjectPropertyModel* model = new QObjectPropertyModel(ui->stackedWidget);
    ui->tableView->setModel(model);
    ui->tableView->setMinimumWidth(300);
#endif
    loadFromSettings();
}



MartletWindow::~MartletWindow()
{
    saveSettings();
    checkFileModified();
    checkProjectModified();
    m_childAppProcess.close();
    delete ui;
}

void MartletWindow::checkFileModified()
{
    if (ui->plainTextEdit->document()->isModified() == true) {
        const QMessageBox::StandardButton btn = QMessageBox::question(this, "Martlet",
                              QString("You have unsaved file '%1'. Do you want to save it ?")
                              .arg(ui->plainTextEdit->property("FileName").toString()),
                              QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        if (btn == QMessageBox::Yes) {
            on_actionSave_File_triggered();
        }
    }

}

void MartletWindow::checkProjectModified()
{
    if (MartletProject::getCurrent() && MartletProject::getCurrent()->isDirty()) {
        on_actionSaveProject_triggered();
    }
}


void MartletWindow::loadFromSettings()
{
    ui->menuRecent_Projects->clear();
    const QVariant pv = MartletSettings::settings().value("projects");
    QStringList sl = pv.toStringList();
    sl.removeDuplicates();
    foreach (QString f, sl) {
        addRecentProject(f);
    }
    connect(m_string_mapper, SIGNAL(mapped(const QString &)),
                 this, SLOT(openProject(const QString &)));
}


void MartletWindow::saveSettings()
{
    const QList<QAction *> alist = ui->menuRecent_Projects->actions();
    QStringList sl;
    foreach (QAction* a, alist) {
        sl.append(a->text());
    }
    sl.removeDuplicates();
    MartletSettings::settings().setValue("projects", sl);
}

void MartletWindow::addRecentProject(const QString& fname)
{
    const QFileInfo fi(fname);
    if (fi.exists()) {
        QAction* a = ui->menuRecent_Projects->addAction(fname);
        connect(a, SIGNAL(triggered()), m_string_mapper, SLOT(map()));
        m_string_mapper->setMapping(a, fname);
    }
}


void MartletWindow::onTestSrated(QVariant name)
{
    qDebug("onTestSrated %s ", qPrintable(name.toString()));
}

void MartletWindow::onTestDone(QVariant name, QVariant status)
{
    qDebug("onTestDone %s ==== %s", qPrintable(name.toString()), qPrintable(status.toString()));
    const QString description = status.toString();
    QColor color = Qt::green;

    if (description.startsWith("FAIL")) {
        color = Qt::red;
    }
    ui->resultsTextEdit->append( QString("<span style=\" color:%1;\">Test <b>%2</b> %3</span>")
                                .arg(color.name())
                                .arg(name.toString())
                                .arg(description));
}

void MartletWindow::onPlaybackFinished()
{
    qDebug("m_client->client()->perform(APP_QUIT_0);");
}

void MartletWindow::onDebug(QVariant type, QVariant message)
{
    ui->logTextEdit->append( QString("%1: %2").arg(type.toString()).arg(message.toString()));
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
    if (index.isValid()) {

        checkFileModified();

        if ( TestFile * tf = getCurrentItem<TestFile>() ) {

            const QString fname = MartletProject::getCurrent()->projectDir()
                                  .filePath(QString::fromStdString( tf->name() ));

            loadFile(fname);
        } else if ( getCurrentItem<TestCase>() )
        {
        } else if ( getCurrentItem<Suite>() )
        {
        } else if ( getCurrentItem<MartletProject>() )
        {
        }

        TestItem* ti = getCurrentItem<TestItem>();
        Q_ASSERT(ti != 0);
        ui->stackedWidget->setCurrentIndex(ti->page());

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

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Select New project file"), AppSettingsDialog::currentDir() , 
                                                    tr("Martlet Project Files (*.mtproject *.mtp)"));
    if (!fileName.isEmpty())
    {

        QFileInfo fi (fileName);
        if (fi.suffix().isEmpty()) {
            fileName.append(".mtp");
        }

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
//            Suite* suite1 = new Suite(pro, "TestSuite1");
//            pro->suites.push_back(suite1);
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
    addRecentProject(QString::fromStdString(MartletProject::getCurrent()->fileName.name()));
}


void MartletWindow::on_actionSave_triggered()
{
    TestFile * tf = getCurrentItem<TestFile>();
    if (tf) {
        const QString fname = MartletProject::getCurrent()->projectDir()
                              .filePath(QString::fromStdString( tf->name() ));
        qDebug("Saving to file %s", qPrintable(fname));
        QFile file( fname );
        file.open(QFile::WriteOnly|QFile::Text|QFile::Truncate);
        const QString txt = ui->plainTextEdit->toPlainText();
        file.write(txt.toLocal8Bit());
        file.close();
        ui->plainTextEdit->document()->setModified(false);
    } else {
        QMessageBox::critical(this, "Martlet Error", "Failed to save file. Select file in tree view first.");
    }

}

void MartletWindow::on_actionOpen_triggered()
{
}

void MartletWindow::on_actionSaveProject_triggered()
{
    if (MartletProject::getCurrent()) {
        MartletProject::getCurrent()->save(); 
    }     
}

void MartletWindow::on_actionSave_As_triggered()
{
//    const QString fname = QString::fromStdString( MartletProject::getCurrent()->currentSuite()->name() );
//    QFile file(fname);
//    file.open(QFile::WriteOnly|QFile::Text|QFile::Truncate);
//    file.write(txt.toLocal8Bit());
//    file.close();
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
        openProject(fileName);
    }
}

void MartletWindow::openProject(const QString & fname)
{
    Q_ASSERT(!fname.isEmpty());
    m_Model->setProject(0);
    delete MartletProject::getCurrent();
    MartletProject::setCurrent(0);

    MartletProject* pro = new MartletProject();
    // load project
    pro->loadFromFile(fname.toStdString());

    MartletProject::setCurrent(pro);

    loadCurrentProjectIntoUI();
    setState<ProjectOpenedState>();
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
//    m_client->tryConnect();
}

void MartletWindow::on_actionRecord_triggered()
{
    Q_ASSERT(MartletProject::getCurrent() != NULL);

    const QMessageBox::StandardButton btn = QMessageBox::question(
            this,
            "Martlet",
            "Would you like to append lines to existing script or replace it ?",
            QMessageBox::Ok|QMessageBox::Reset,
            QMessageBox::Ok);

    if (btn == QMessageBox::Reset) {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->document()->setModified(true);
    }
    m_mode_play = false;
    startApp();
}

void MartletWindow::startApp()
{
    if( m_childAppProcess.state() != QProcess::Running) {
        Q_ASSERT(MartletProject::getCurrent() != NULL);
        const QString app = QString("./martex ") +
           QDir::cleanPath(
               MartletProject::getCurrent()->projectDir().filePath(
                     QString::fromStdString(
                            MartletProject::getCurrent()->executable.name())));

        qDebug("Starting app '%s'", qPrintable(app));
        Q_ASSERT( !app.isEmpty() );
        qDebug("Starting listener client.");
            m_client->startListening();
//        tryConnectAndStart();
        qDebug("Starting App.");
        m_childAppProcess.start(app);
//        m_childAppProcess.waitForStarted();
    } else { // restart
        qDebug("Stopping App.");
        m_childAppProcess.close();
        m_childAppProcess.waitForFinished(1000);
        startApp();
    }
}

void MartletWindow::tryConnectAndStart()
{
    connect(m_client->client(), SIGNAL(connected()),
            this, SLOT(onTestedAppConnected()));
    m_client->startListening();
}

void MartletWindow::onMartexConnected()
{

}

void MartletWindow::onTestedAppConnected()
{
    if (m_mode_play)
    {
        qDebug("Play script ... ");
        m_client->uploadScript("H.qs", ui->plainTextEdit->toPlainText());
        m_client->play("H.qs");
        qDebug("Remote Playback started");
    } else {
        qDebug("Record script ... ");
        m_client->startRecording("f.qs");
    }
    ui->logTextEdit->clear();
    ui->resultsTextEdit->append("\n Starting new session: ");
    ui->resultsTextEdit->append(QDateTime::currentDateTime().toString());
    if (ui->resultsTextEdit->verticalScrollBar()) {
        ui->resultsTextEdit->verticalScrollBar()->setValue(30000);
    }

}


void MartletWindow::on_actionStop_recording_triggered()
{
    qDebug("void MartletWindow::on_actionStop_recording_triggered()");
    m_client->stopRecording("f.qs");
    m_client->askForRecordedText("f.qs");
    qDebug("Waitinng for text from client ....");
}

void MartletWindow::on_actionPlay_triggered()
{
    m_mode_play = true;
    startApp();
//    m_childAppProcess.waitForStarted();

//    m_client->disconnect();
//    do {
//        for (int i = 0; i < 6; ++i) { // TODO: small delay needed
//            QApplication::processEvents();
//        }
//    } while (!m_client->isConnected());

}

void MartletWindow::on_pushButton_4_clicked() // play
{
    on_actionPlay_triggered();
}

void MartletWindow::onRecordedTextUpdate(const QVariant& txt)
{
    qDebug() << "Text arrived to main window" << txt;
    ui->plainTextEdit->appendPlainText( txt.toString() );
    ui->plainTextEdit->document()->setModified(true);

    QTimer::singleShot(500, m_client, SLOT(onPlaybackFinished()));

//    const QString fname = QString::fromStdString( MartletProject::getCurrent()->currentSuite()->name() );
//    QFile file(fname);
//    file.open(QFile::WriteOnly|QFile::Text|QFile::Truncate);
//    file.write(txt.toLocal8Bit());
//    file.close();

    m_childAppProcess.close();
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
    Suite * suite = getCurrentItem<Suite>();
    if (suite) {
        std::vector<Suite *>::iterator i =
                std::find(MartletProject::getCurrent()->suites.begin(), MartletProject::getCurrent()->suites.end(), suite);
        if (i != MartletProject::getCurrent()->suites.end()) {
            MartletProject::getCurrent()->suites.erase(i, i+1);
            delete suite;
            loadCurrentProjectIntoUI();
        }
    }
}

void MartletWindow::on_actionSuite_Add_Test_Case_triggered()
{
    Suite * testCase = getCurrentItem<Suite>();
    if (testCase) {
        const QString n = QInputDialog::getText(this, "Enter test case name", "Test Case name");
        if (!n.isEmpty())  {
            testCase->testCases.push_back(new TestCase(testCase, n));
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
        QString n = QInputDialog::getText(this, "Enter test file name", "Test File name");
        if (!n.isEmpty())  {
            const QFileInfo fi(n);
            if (fi.suffix().isEmpty()) {
                n.append(".qs");
            }
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

void MartletWindow::loadFile(const QString& fname)
{
    qDebug("Loading file %s", qPrintable(fname));
    QFile file(fname);
    file.open(QFile::ReadOnly|QFile::Text|QFile::Truncate);
    QString txt = file.readAll();
    file.close();
    // load file
    ui->plainTextEdit->setPlainText( txt );
    ui->plainTextEdit->setProperty("FileName", fname);
    ui->plainTextEdit->document()->setModified(false);
}

void MartletWindow::on_actionSave_File_triggered()
{
//    TestFile * tf = getCurrentItem<TestFile>();
//    if (tf) {
        const QString txt = ui->plainTextEdit->toPlainText();
        QString fname = ui->plainTextEdit->property("FileName").toString();

        Q_ASSERT(!fname.isEmpty());
        if (!txt.isEmpty() && !fname.isEmpty())  {
//            fname = MartletProject::getCurrent()->projectDir()
//                                          .filePath( fname );
            qDebug("Saving file %s", qPrintable(fname));
            QFile file(fname);
            file.open(QFile::WriteOnly|QFile::Text|QFile::Truncate);
            file.write(txt.toLocal8Bit());
            file.close();
            ui->plainTextEdit->document()->setModified(false);
        }
//    }
}

void MartletWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "Martlet", "Qt GUI automation testing application\nAuthors: Oleksandr Omelchuk, Anatolii Kyrylyuk\nLicense: GPL\n");
}

void MartletWindow::on_actionExit_triggered()
{
    close();
}
