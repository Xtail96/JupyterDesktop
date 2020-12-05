#include <QApplication>
#include <QWebEngineView>
#include <QThread>
#include "launcher/jupyter_lab_launcher.h"
#include "settings_manager/settings_manager.h"
#include "configuration_dialog.h"

void configure()
{
    qDebug() << "configure";
    ConfigurationDialog(nullptr).exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //if(!SettingsManager::settingsFileExists()) configure();

    configure();

    SettingsManager sm;
    JupyterLabLauncher launcher(sm.get("Main", "ServerPath").toString(), sm.get("Main", "WorkingDir").toString(), nullptr);
    launcher.launch();

    // пауза, чтобы сервер запустился
    QThread::sleep(sm.get("Main", "LaunchTimeout").toInt());

    QWebEngineView *view = new QWebEngineView(nullptr);
    view->load(QUrl(sm.get("Main", "ClientUrl").toString()));
    view->showMaximized();

    return a.exec();
}
