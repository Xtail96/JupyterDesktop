#include <QApplication>
#include <QWebEngineView>
#include <QThread>
#include <QMenuBar>
#include <QMessageBox>

#include "launcher/jupyter_lab_launcher.h"
#include "settings_manager/settings_manager.h"
#include "gui/configuration_dialog.h"
#include "gui/splash_screen_dialog.h"

int configure()
{
    return ConfigurationDialog(nullptr).exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!SettingsManager::settingsFileExists()) configure();

    // Добавляем в меню вызов диалога для повторной настройки сситемы
    QMenuBar mainMenuBar;
    QScopedPointer<QMenu> mainMenu(new QMenu("&Menu"));
    mainMenu->addAction("&Preferences", [=]() {
        if(configure() == QDialog::Accepted)
            QMessageBox(QMessageBox::Information, "", "Please restart the application to apply settings.").exec();
    });
    mainMenuBar.addMenu(mainMenu.data());
    mainMenuBar.show();

    // Запускаем сервер
    SettingsManager sm;
    JupyterLabLauncher launcher(sm.get("General", "ServerPath").toString(), sm.get("General", "WorkingDir").toString(), nullptr);
    launcher.launch();

    // Пауза, чтобы сервер успел запуститься
    QScopedPointer<SplashScreenDialog> splash(new SplashScreenDialog(nullptr));
    splash->show();
    QApplication::processEvents();
    QThread::sleep(sm.get("General", "LaunchTimeout").toInt());
    splash->close();

    // Отображаем клиентскую страницу
    QScopedPointer<QWebEngineView> view(new QWebEngineView(nullptr));
    view->load(QUrl(sm.get("General", "ClientUrl").toString()));
    view->showMaximized();

    return a.exec();
}
