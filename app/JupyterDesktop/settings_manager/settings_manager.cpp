#include "settings_manager.h"

SettingsManager::SettingsManager() : SettingsManager(DEFAULT_SETTINGS_FILE)
{
}

SettingsManager::SettingsManager(QString settingsFile)
{
#ifdef Q_OS_MACX
    QString settingsPath = qApp->applicationDirPath() + "/" + settingsFile;
#else
    QString settingsPath = DEFAULT_SETTINGS_DIR + settingsFile;
#endif

    // проверка на существование файла с настройками
    if (this->settingsFileExists(settingsFile))
    {
        // если не существует, выводим соответствующее сообщение
        qInfo() << "Settings file not found. Generate default settings.";

        // используем настройки по умолчанию
        settings = std::shared_ptr<QSettings>( new QSettings(settingsPath, QSettings::IniFormat) );
        // используем кодировку юникод
        settings->setIniCodec("UTF-8");

        generateDefaultSettings();
    }
    else
    {
        settings = std::shared_ptr<QSettings>( new QSettings(settingsPath, QSettings::IniFormat) );
        // используем кодировку юникод
        settings->setIniCodec("UTF-8");
    }
}

void SettingsManager::importSettings(QString settingsPath)
{
    // проверка на существование файла с настройками
    if (QFileInfo::exists(settingsPath))
    {
        // получение настроек из файла по указанному пути
        QSettings importSettings(settingsPath, QSettings::IniFormat);

        // перезапись основных настроек
        for (QString key : importSettings.allKeys())
        {
            settings->setValue(key, importSettings.value(key));
        }

        // сохранение основных настроек
        saveSettings();
    }
}

SettingsManager::~SettingsManager()
{
    // сохраняем настройки перед выходом
    saveSettings();
}

void SettingsManager::saveSettings()
{
    settings->sync();
}

void SettingsManager::exportSettings(QString path)
{
    QSettings expSettings(path, QSettings::IniFormat);

    for (QString key : settings->allKeys())
    {
        expSettings.setValue(key, settings->value(key));
    }

    expSettings.sync();
}

QVariant SettingsManager::get(QString group, QString key) const
{
    QVariant value;

    settings->beginGroup(group);

    if (settings->contains(key))
    {
        value = settings->value(key);
    }
    else
    {
        settings->endGroup();

        QString message = QStringLiteral("В файла настроек отсутствует ключ ") + key + QStringLiteral(" для секции ") + group;
        throw std::invalid_argument(message.toStdString());
    }

    settings->endGroup();

    return value;
}

void SettingsManager::set(QString group, QString key, QVariant value)
{
    settings->beginGroup(group);
        settings->setValue(key, value);
    settings->endGroup();
}

void SettingsManager::generateDefaultSettings()
{
    settings->beginGroup("Main");
        settings->setValue("ClientUrl", "http://localhost:8888/lab");
        settings->setValue("LaunchTimeout", 5);
        settings->setValue("WorkingDir", "/Users/xtail");
        settings->setValue("ServerPath", "usr/local/bin/jupyter-lab");
    settings->endGroup();

    // применяем изменения
    saveSettings();
}

QStringList SettingsManager::settingsKeys()
{
    return settings->allKeys();
}

bool SettingsManager::settingsFileExists(QString settingsFile)
{
    return QFileInfo::exists(settingsFile);
}
