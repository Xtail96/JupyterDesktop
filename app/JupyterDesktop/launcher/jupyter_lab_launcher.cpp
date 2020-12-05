#include "jupyter_lab_launcher.h"

JupyterLabLauncher::JupyterLabLauncher(QObject *parent) :
    QObject(parent),
    m_lab(this),
    m_labPath("/usr/local/bin/jupyter-lab"),
    m_workingDir("/Users/xtail")
{ 
}

JupyterLabLauncher::~JupyterLabLauncher()
{
    this->terminate();
}

void JupyterLabLauncher::launch()
{
    m_lab.setWorkingDirectory(m_workingDir);
    m_lab.start(m_labPath);
    m_lab.waitForStarted(-1);
}

void JupyterLabLauncher::terminate()
{
    m_lab.kill();
    m_lab.waitForFinished(-1);
}
