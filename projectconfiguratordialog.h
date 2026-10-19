#ifndef PROJECTCONFIGURATORDIALOG_H
#define PROJECTCONFIGURATORDIALOG_H

#include <QDialog>

namespace Ui {
class ProjectConfiguratorDialog;
}

class ProjectConfiguratorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectConfiguratorDialog(QWidget *parent = nullptr);
    ~ProjectConfiguratorDialog();

private:
    Ui::ProjectConfiguratorDialog *ui;
};

#endif // PROJECTCONFIGURATORDIALOG_H
