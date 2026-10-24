#include "configuredialog.h"
#include "ui_configuredialog.h"

ConfigureDialog::ConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfigureDialog)
{
    ui->setupUi(this);
}

ConfigureDialog::~ConfigureDialog()
{
    delete ui;
}

QString ConfigureDialog::getMusicDir() const {
    return ui->musicBaseDirEdit->text();
}

QString ConfigureDialog::getProjectsDir() const {
    return ui->projectDirBaseEdit->text();
}
void ConfigureDialog::setMusicDir(const QString & text) {
    ui->musicBaseDirEdit->setText(text);
}

void ConfigureDialog::setProjectsDir(const QString & text) {
    ui->projectDirBaseEdit->setText(text);
}
