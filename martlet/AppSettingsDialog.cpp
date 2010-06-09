#include "AppSettingsDialog.h"
#include "ui_AppSettingsDialog.h"

AppSettingsDialog::AppSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppSettingsDialog)
{
    ui->setupUi(this);
}

AppSettingsDialog::~AppSettingsDialog()
{
    delete ui;
}

void AppSettingsDialog::changeEvent(QEvent *e)
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
