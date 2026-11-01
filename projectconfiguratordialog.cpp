#include "projectconfiguratordialog.h"
#include "ui_projectconfiguratordialog.h"
#include "pendrivesupport.h"
#include <QPushButton>

#define DO_NOT_INITIALIZE "<do not intialize pendrive>"
#define PENDRIVE_STATUS_OK ""
#define PENDRIVE_STATUS_ERROR "Pendrive is not empty"

ProjectConfiguratorDialog::ProjectConfiguratorDialog(QWidget *parent, ProjectConfig * existingProjectConfig)
    : QDialog(parent)
    , ui(new Ui::ProjectConfiguratorDialog)
{
    ui->setupUi(this);

    //todo use dat existingProjectConfig

    connect(ui->pendrivePathCombo, &QComboBox::activated, this, &ProjectConfiguratorDialog::validateSelectedPendrivePath);
    //TODO disable if name is empty
    //ui->pendriveConfigurationButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

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
    ui->pendrivePathStatusLabel->setStyleSheet("color: red;");
}
QStringList ProjectConfiguratorDialog::getAvailablePendrivePaths(){

    QStringList l = PendriveSupport::getAvailablePendrives();
    l.push_front(DO_NOT_INITIALIZE);
    return l;
}

void ProjectConfiguratorDialog::validateSelectedPendrivePath(int i)
{

    QString selectedPath = ui->pendrivePathCombo->itemText(i);
    bool statusOk = false;

    // <do not initialize> is not blocking "OK" button
    // otherwise selected pendrive must be empty
    statusOk=selectedPath == DO_NOT_INITIALIZE ? true : PendriveSupport::canPendriveBeInitialized(selectedPath);

    ui->pendriveConfigurationButtonBox->button(QDialogButtonBox::Ok)->setEnabled(statusOk);
    ui->pendrivePathStatusLabel->setText(statusOk ? PENDRIVE_STATUS_OK : PENDRIVE_STATUS_ERROR);
}

ProjectConfiguratorDialog::~ProjectConfiguratorDialog()
{
    delete ui;
}

ProjectConfig ProjectConfiguratorDialog::getProjectConfig() const {
    ProjectConfig p;
    p.key = ui->configurationNameEdit->text();
    p.path = ui->pendrivePathCombo->currentText();
    p.type = ui->pendriveTypeCombo->currentText();
    return p;
}

void ProjectConfiguratorDialog::accept()
{
    QString selectedPath = ui->pendrivePathCombo->currentText();
    if (selectedPath != DO_NOT_INITIALIZE) {
        PendriveSupport::initializePendrive(selectedPath,ui->configurationNameEdit->text());
        // TODO
        qDebug() << "wil initialize " << selectedPath << " project: " << ui->configurationNameEdit->text();
    }
    QDialog::accept();
}


