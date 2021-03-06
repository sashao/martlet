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


#ifndef MARTLETWINDOW_H
#define MARTLETWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QModelIndex>
#include "MartletClient.h"
#include "MartletServer.h"

namespace Ui {
    class MartletWindow;
}

class MProjectModel;
class QSignalMapper;

class MartletWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MartletWindow(QWidget *parent = 0);
    ~MartletWindow();

protected:
    class State {
    public:
        virtual void visit(MartletWindow* /*mw*/) = 0;
    };

    class InitState : public State {
    public:
        virtual void visit(MartletWindow* /*mw*/) {
            
        }
    };
    
    class ProjectOpenedState : public State {
    public:
        virtual void visit(MartletWindow* /*mw*/) {
            
        }
    };
    
    template <class ST>
    void setState() {
        ST state;
        state.visit(this);
    }

    template <class C>
    C* getCurrentItem();

    void loadCurrentProjectIntoUI();
    
    void changeEvent(QEvent *e);

private:
    Ui::MartletWindow *ui;
    MartletClient* m_client;
//    MartletServer* m_server;
    MProjectModel* m_Model;
    QProcess m_childAppProcess;
    bool m_mode_play;
    QSignalMapper* m_string_mapper;

    void startApp();
    void loadFromSettings();
    void saveSettings();
    void checkFileModified();
    void checkProjectModified();
    void addRecentProject(const QString& fname);
    
private slots:
    void on_actionExit_triggered();
    void openProject(const QString & fname);
    void onRecordedTextUpdate(const QVariant& txt);
    void on_actionStop_recording_triggered();
    void on_actionPlay_triggered();
    void on_actionRecord_triggered();
    void on_actionStart_program_triggered();
    void on_actionDelete_existing_suite_triggered();
    void on_actionNew_Suite_triggered();
    void on_actionLoad_triggered();
    void on_actionSave_As_triggered();
    void on_actionSaveProject_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_pushButton_4_clicked();
    void on_pushButton_3_toggled(bool checked);
    void on_treeView_customContextMenuRequested ( const QPoint & pos );

    void tryConnectAndStart();
    void onMartexConnected();
    void onTestedAppConnected();
    void onTestSrated(QVariant);
    void onTestDone(QVariant, QVariant);
    void onDebug(QVariant, QVariant);
    void onPlaybackFinished();

    void on_actionProject_Add_suite_triggered();
    void on_actionSuite_Delete_triggered();
    void on_actionSuite_Add_Test_Case_triggered();
    void on_actionTK_Delete_triggered();
    void on_actionTK_Add_File_triggered();
    void on_actionRecord_from_scratch_triggered();
    void on_actionFile_Delete_From_Suite_triggered();
    void on_actionFile_Delete_Phisically_triggered();
    void on_treeView_clicked(QModelIndex index);
    void loadFile(const QString& fname);
    void on_actionSave_File_triggered();
    void on_actionAbout_triggered();
};

#endif // MARTLETWINDOW_H
