#include <QApplication>
#include <QWebEngineView>
#include <QThread>
#include "launcher/jupyter_lab_launcher.h"
#include "settings_manager/settings_manager.h"
#include "gui/configuration_dialog.h"
#include "gui/splash_screen_dialog.h"

#include <QLabel>

void configure()
{
    ConfigurationDialog(nullptr).exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!SettingsManager::settingsFileExists()) configure();

    SettingsManager sm;
    JupyterLabLauncher launcher(sm.get("General", "ServerPath").toString(), sm.get("General", "WorkingDir").toString(), nullptr);
    launcher.launch();

    // пауза, чтобы сервер запустился
    QScopedPointer<SplashScreenDialog> splash(new SplashScreenDialog(nullptr));
    splash->show();
    QApplication::processEvents();
    QThread::sleep(sm.get("General", "LaunchTimeout").toInt());
    splash->close();

    QScopedPointer<QWebEngineView> view(new QWebEngineView(nullptr));
    view->load(QUrl(sm.get("General", "ClientUrl").toString()));
    view->showMaximized();

    return a.exec();
}
