#ifndef JUPYTERLABLAUNCHER_H
#define JUPYTERLABLAUNCHER_H

#include <QObject>
#include <QProcess>
#include <QDebug>

class JupyterLabLauncher : public QObject
{
    Q_OBJECT
public:
    explicit JupyterLabLauncher(QString jupyterLabPath, QString workingDirectory, QObject *parent = nullptr);
    ~JupyterLabLauncher();

    void launch();
    void terminate();

signals:
    void ready();

private:
    QProcess m_jupyterLabProcess;
    QString m_jupyterLabPath;
    QString m_workingDir;


};

#endif // JUPYTERLABLAUNCHER_H
