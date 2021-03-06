#include "splash_screen_dialog.h"
#include "ui_splash_screen_dialog.h"

SplashScreenDialog::SplashScreenDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::SplashScreenDialog)
{
    ui->setupUi(this);

    QPixmap p(":/images/574595169.png");
    ui->label->setPixmap(p);
    ui->label->setScaledContents(true);
}

SplashScreenDialog::~SplashScreenDialog()
{
    delete ui;
}
