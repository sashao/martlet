#ifndef MARTLETWINDOW_H
#define MARTLETWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MartletWindow;
}

class MartletWindow : public QMainWindow {
    Q_OBJECT
public:
    MartletWindow(QWidget *parent = 0);
    ~MartletWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MartletWindow *ui;
};

#endif // MARTLETWINDOW_H
