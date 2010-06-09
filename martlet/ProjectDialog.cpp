#include "ProjectDialog.h"
#include "ui_ProjectDialog.h"
#include "MartletProject.h"
        
ProjectDialog::ProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectDialog),
    m_pro(0)
{
    ui->setupUi(this);
}

ProjectDialog::~ProjectDialog()
{
    delete ui;
}

void ProjectDialog::setProject(MartletProject* pro)
{
    Q_ASSERT(pro != 0);
    m_pro = pro;
    ui->filenameEdit->setText(pro->fileName);
    ui->executableName->setText(pro->executable);
    ui->typeComboBox->setCurrentIndex(ui->typeComboBox->findText(pro->type));
}

void ProjectDialog::populateToproject()
{
    Q_ASSERT(m_pro != 0);
    qDebug("ProjectDialog: Populating updated information to project.");
    m_pro->fileName = ui->filenameEdit->text();
    m_pro->executable = ui->executableName->text();
    m_pro->type = ui->typeComboBox->currentText();
}


void ProjectDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ProjectDialog::on_fnameButton_clicked()
{
    
}

void ProjectDialog::on_execButton_clicked()
{
    
}

void ProjectDialog::on_buttonBox_accepted()
{
    populateToproject(); 
}
