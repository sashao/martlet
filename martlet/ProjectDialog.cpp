#include "ProjectDialog.h"
#include "ui_ProjectDialog.h"
#include "MartletProject.h"
#include "AppSettingsDialog.h"
#include <QFileDialog>
#include <QPushButton>



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
    const QString rfn = m_pro->projectDir().relativeFilePath(
            ui->executableName->text());
    m_pro->executable.setName( rfn.toStdString() );
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
    QString fname = QFileDialog::getSaveFileName(this,
                                                 tr("Select New project file"), AppSettingsDialog::currentDir() ,
                                                 tr("Martlet Project Files (*.mtproject *.mtp)"));

    if (!fname.isEmpty()) {
        QFileInfo fi (fname);
        if (fi.suffix().isEmpty()) {
            fname.append(".mtp");
        }
        ui->filenameEdit->setText(fname);
    }
}

void ProjectDialog::on_execButton_clicked()
{
    const QString fname = QFileDialog::getOpenFileName(
                this,
                "Select executable"
                "",
                "Executables (*)"

                );
    if (!fname.isEmpty()) {
        ui->executableName->setText(fname);
    }
}

void ProjectDialog::on_buttonBox_accepted()
{
    populateToProject();
}

void ProjectDialog::on_filenameEdit_textChanged(const QString &arg1)
{
    ui->executableName->setEnabled(!arg1.isEmpty());
}

void ProjectDialog::on_executableName_textChanged(const QString &arg1)
{
    QFileInfo fi(arg1);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(
            !arg1.isEmpty() && fi.exists() && ui->executableName->isEnabled());
}
