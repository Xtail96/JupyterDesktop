#include "jupyter_lab_launcher.h"

JupyterLabLauncher::JupyterLabLauncher(QString jupyterLabPath, QString workingDirectory, QObject *parent) :
    QObject(parent),
    m_jupyterLabProcess(this),
    m_jupyterLabPath(jupyterLabPath),
    m_workingDir(workingDirectory)
{ 
}

JupyterLabLauncher::~JupyterLabLauncher()
{
    this->terminate();
}

void JupyterLabLauncher::launch()
{
    m_jupyterLabProcess.setWorkingDirectory(m_workingDir);
    m_jupyterLabProcess.start(m_jupyterLabPath);
    m_jupyterLabProcess.waitForStarted(-1);
}

void JupyterLabLauncher::terminate()
{
    m_jupyterLabProcess.kill();
    m_jupyterLabProcess.waitForFinished(-1);
}
