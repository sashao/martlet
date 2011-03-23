//    Martlet - application automated Qt GUI application testing and more.
//    Copyright (C) 2010  Oleksandr Omelchuk sashao@e-mail.ua

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


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

