#ifndef MARTLETWINDOW_H
#define MARTLETWINDOW_H

#include <QMainWindow>
#include "MartletClient.h"
#include "MartletServer.h"

namespace Ui {
    class MartletWindow;
}

class MProjectModel;

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
    MartletServer* m_server;
    MProjectModel* m_Model;
    QProcess m_childAppProcess;

    void startApp();
    
private slots:
    void onRecordedTextUpdate(QString txt);
    void on_actionStop_recording_triggered();
    void on_actionPlay_triggered();
    void on_actionRecord_triggered();
    void on_actionStart_program_triggered();
    void on_actionDelete_existing_suite_triggered();
    void on_actionNew_Suite_triggered();
    void on_actionLoad_triggered();
    void on_actionSave_As_triggered();
    void on_actionSave_2_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_pushButton_4_clicked();
    void on_pushButton_3_toggled(bool checked);
    void on_treeView_customContextMenuRequested ( const QPoint & pos );

    void tryConnectAndStart();
    void on_actionProject_Add_suite_triggered();
    void on_actionSuite_Delete_triggered();
    void on_actionSuite_Add_Test_Case_triggered();
    void on_actionTK_Delete_triggered();
    void on_actionTK_Add_File_triggered();
    void on_actionRecord_from_scratch_triggered();
    void on_actionFile_Delete_From_Suite_triggered();
    void on_actionFile_Delete_Phisically_triggered();
    void on_treeView_clicked(QModelIndex index);
};

#endif // MARTLETWINDOW_H
