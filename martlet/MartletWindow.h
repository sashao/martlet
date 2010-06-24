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
    
    void loadCurrentProjectIntoUI();
    
    void changeEvent(QEvent *e);

private:
    Ui::MartletWindow *ui;
    MartletClient* m_client;
    MartletServer* m_server;
    MProjectModel* m_Model;
    
private slots:
    void onRecordedTextUpdate(QString txt);
    void on_pushButton_3_clicked();
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
};

#endif // MARTLETWINDOW_H
