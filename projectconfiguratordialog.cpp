#include "projectconfiguratordialog.h"
#include "ui_projectconfiguratordialog.h"

ProjectConfiguratorDialog::ProjectConfiguratorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProjectConfiguratorDialog)
{
    ui->setupUi(this);

    // configuration name validaton: to be only uppercase and numbers
    ui->configurationNameEdit->setMaxLength(24);
    connect(ui->configurationNameEdit, &QLineEdit::textEdited, this, [this](const QString &text) {
        int cursorPosition = ui->configurationNameEdit->cursorPosition();
        int oldLength = text.length();
        QString cleanedText = text.toUpper();

        QRegularExpression nonAlphanumeric("[^A-Z0-9_]");
        cleanedText.remove(nonAlphanumeric);
        ui->configurationNameEdit->setText(cleanedText);
        int newLength = cleanedText.length();
        if (newLength < oldLength) {
            cursorPosition -= (oldLength - newLength);
        }
        ui->configurationNameEdit->setCursorPosition(qMax(0, cursorPosition));
    });

    ui->pendrivePathCombo->addItems(getAvailablePendrivePaths());
}
QStringList ProjectConfiguratorDialog::getAvailablePendrivePaths(){
    QStringList l;
    l.push_back("<do not intialize pendrive>");
    l.push_back("A:\\");
    l.push_back("E:\\");
    return l;

}

ProjectConfiguratorDialog::~ProjectConfiguratorDialog()
{
    delete ui;
}

ProjectConfig ProjectConfiguratorDialog::getProjectConfig() const{
    ProjectConfig p;
    p.key = ui->configurationNameEdit->text();
    p.path = ui->pendrivePathCombo->currentText();
    p.type = ui->pendriveTypeCombo->currentText();
    return p;
}
