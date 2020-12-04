#ifndef JUPYTERLABLAUNCHER_H
#define JUPYTERLABLAUNCHER_H

#include <QObject>
#include <QProcess>
#include <QDebug>

class JupyterLabLauncher : public QObject
{
    Q_OBJECT
public:
    explicit JupyterLabLauncher(QObject *parent = nullptr);
    ~JupyterLabLauncher();

    void launch();
    void terminate();

signals:
    void ready();

private:
    QProcess m_lab;
    QString m_labPath;
    QString m_workingDir;


};

#endif // JUPYTERLABLAUNCHER_H
