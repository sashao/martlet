#include "MartletSettings.h"
#include <QApplication>

MartletSettings::MartletSettings(QObject *parent)
    : QObject(parent)
    , m_settings("Martlet", "Martlet")
{
}

MartletSettings* MartletSettings::m_instance = 0;

MartletSettings& MartletSettings::instance()
{
    if (m_instance == 0) {
        m_instance = new MartletSettings(QApplication::instance());
    }
    return *m_instance;
}

QSettings& MartletSettings::settings()
{
    return instance().m_settings;
}

