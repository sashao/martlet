#ifndef APPSETTINGSDIALOG_H
#define APPSETTINGSDIALOG_H

#include <QDialog>
#include <QDir>

namespace Ui {
    class AppSettingsDialog;
}

class AppSettingsDialog : public QDialog {
    Q_OBJECT
public:
    AppSettingsDialog(QWidget *parent = 0);
    ~AppSettingsDialog();
    
    static QString currentDir() {
        return QDir::currentPath();
    }

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AppSettingsDialog *ui;
};

#endif // APPSETTINGSDIALOG_H
