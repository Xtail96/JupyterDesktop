#include "splash_screen_dialog.h"
#include "ui_splash_screen_dialog.h"

SplashScreenDialog::SplashScreenDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::SplashScreenDialog)
{
    ui->setupUi(this);

    QPixmap p(":/images/jupyter_logo.jpeg");
    ui->label->setPixmap(p);
    ui->label->setScaledContents(true);
}

SplashScreenDialog::~SplashScreenDialog()
{
    delete ui;
}
