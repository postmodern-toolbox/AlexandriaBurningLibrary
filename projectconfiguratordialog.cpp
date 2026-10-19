#include "projectconfiguratordialog.h"
#include "ui_projectconfiguratordialog.h"

ProjectConfiguratorDialog::ProjectConfiguratorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProjectConfiguratorDialog)
{
    ui->setupUi(this);
}

ProjectConfiguratorDialog::~ProjectConfiguratorDialog()
{
    delete ui;
}
