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
    void on_filenameEdit_textChanged(const QString &arg1);
    void on_executableName_textChanged(const QString &arg1);
};

#endif // PROJECTDIALOG_H
