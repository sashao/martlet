#ifndef PROJECTDIALOG_H
#define PROJECTDIALOG_H

#include <QDialog>

namespace Ui {
    class ProjectDialog;
}

class MartletProject;

class ProjectDialog : public QDialog {
    Q_OBJECT
public:
    ProjectDialog(QWidget *parent = 0);
    ~ProjectDialog();
    
    void setProject(MartletProject* pro);
    
protected:
    void populateToProject();
            
    void changeEvent(QEvent *e);

private:
    Ui::ProjectDialog *ui;
    MartletProject* m_pro;

private slots:
    void on_buttonBox_accepted();
    void on_execButton_clicked();
    void on_fnameButton_clicked();
};

#endif // PROJECTDIALOG_H
