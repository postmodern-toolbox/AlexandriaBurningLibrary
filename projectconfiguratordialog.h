#ifndef PROJECTCONFIGURATORDIALOG_H
#define PROJECTCONFIGURATORDIALOG_H

#include <QDialog>
#include "projectconfig.h"


namespace Ui {
class ProjectConfiguratorDialog;
}

class ProjectConfiguratorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectConfiguratorDialog(QWidget *parent = nullptr);
    ~ProjectConfiguratorDialog();

    ProjectConfig getProjectConfig() const;

private:
    Ui::ProjectConfiguratorDialog *ui;

    QStringList getAvailablePendrivePaths();
};

#endif // PROJECTCONFIGURATORDIALOG_H
