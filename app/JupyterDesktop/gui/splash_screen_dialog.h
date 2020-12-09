#ifndef SPLASH_SCREEN_DIALOG_H
#define SPLASH_SCREEN_DIALOG_H

#include <QDialog>
#include <QPicture>

namespace Ui {
class SplashScreenDialog;
}

class SplashScreenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SplashScreenDialog(QWidget *parent = nullptr);
    ~SplashScreenDialog();

private:
    Ui::SplashScreenDialog *ui;
};

#endif // SPLASH_SCREEN_DIALOG_H
