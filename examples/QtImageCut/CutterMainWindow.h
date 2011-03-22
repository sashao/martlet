#ifndef CUTTERMAINWINDOW_H
#define CUTTERMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class CutterMainWindow;
}

class CutterMainWindow : public QMainWindow 
{
    Q_OBJECT
public:
    CutterMainWindow(QWidget *parent = 0);
    ~CutterMainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CutterMainWindow *ui;

private slots:
    void on_actionAuto_select_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
};

#endif // CUTTERMAINWINDOW_H
