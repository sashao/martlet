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
    ui->filenameEdit->setText( QString::fromStdString(pro->fileName.name()));
    ui->executableName->setText(QString::fromStdString(pro->executable.name()));
    ui->typeComboBox->setCurrentIndex(ui->typeComboBox->findText(QString::fromStdString(pro->type.name())));
}

void ProjectDialog::populateToProject()
{
    Q_ASSERT(m_pro != 0);
    qDebug("ProjectDialog: Populating updated information to project.");
    m_pro->fileName .setName(ui->filenameEdit->text().toStdString());
    m_pro->executable.setName( ui->executableName->text().toStdString());
    m_pro->type.setName( ui->typeComboBox->currentText().toStdString());
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
    populateToProject();
}
