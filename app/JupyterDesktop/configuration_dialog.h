#ifndef CONFIGURATION_DIALOG_H
#define CONFIGURATION_DIALOG_H

#include <QDialog>
#include "settings_manager/settings_manager.h"

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = nullptr);
    ~ConfigurationDialog();

private:
    Ui::ConfigurationDialog *ui;

    void fillSettings();
};

#endif // CONFIGURATION_DIALOG_H
