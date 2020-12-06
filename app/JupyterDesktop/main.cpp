#include <QApplication>
#include <QWebEngineView>
#include <QThread>
#include "launcher/jupyter_lab_launcher.h"
#include "settings_manager/settings_manager.h"
#include "gui/configuration_dialog.h"

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
    QThread::sleep(sm.get("General", "LaunchTimeout").toInt());

    QWebEngineView *view = new QWebEngineView(nullptr);
    view->load(QUrl(sm.get("General", "ClientUrl").toString()));
    view->showMaximized();

    return a.exec();
}
