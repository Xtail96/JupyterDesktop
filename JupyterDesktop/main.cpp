#include <QApplication>
#include <QWebEngineView>
#include <QThread>
#include "jupyter_lab_launcher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    JupyterLabLauncher launcher;
    launcher.launch();

    // пауза, чтобы сервер запустился
    QThread::sleep(5);

    QWebEngineView *view = new QWebEngineView(nullptr);
    view->load(QUrl("http://localhost:8888/lab"));
    view->showMaximized();

    return a.exec();
}
