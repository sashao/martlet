#ifndef MARTLETWINDOW_H
#define MARTLETWINDOW_H

#include <QMainWindow>
#include "MartletClient.h"
#include "MartletServer.h"

namespace Ui {
    class MartletWindow;
}


class MartletWindow : public QMainWindow {
    Q_OBJECT
public:
    MartletWindow(QWidget *parent = 0);
    ~MartletWindow();

protected:
    class State {
    public:
        virtual void visit(MartletWindow* mw) = 0;
    };

    class InitState : public State {
    public:
        virtual void visit(MartletWindow* mw) {
            
        }
    };
    
    class ProjectOpenedState : public State {
    public:
        virtual void visit(MartletWindow* mw) {
            
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

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_toggled(bool checked);
};

#endif // MARTLETWINDOW_H
