/*
 PortableQtApp template
 Copyright (C) 2018 Pedro Lopez-Cabanillas <plcl@users.sf.net>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include "portablesettings.h"

PortableSettings::PortableSettings(QObject *parent) : QObject(parent)
{
    ResetDefaults();
}

PortableSettings::~PortableSettings()
{
    resetSettings();
}

PortableSettings *PortableSettings::instance()
{
    static PortableSettings inst;
    return &inst;
}

QSettings *PortableSettings::settingsInstance()
{
    if (m_settings == nullptr) {
        if (m_portableConfigFile.isEmpty()) {
            QSettings::setDefaultFormat(QSettings::NativeFormat);
            m_settings = new QSettings();
        } else {
            m_settings = new QSettings(m_portableConfigFile, QSettings::IniFormat);
        }
    }
    return m_settings;
}

void PortableSettings::resetSettings()
{
    Save();
    delete m_settings;
}

void PortableSettings::ResetDefaults()
{
    m_boolOption = false;
    m_choiceOption = QString();
    m_textOption = QString();
    m_integerOption = 0;
    emit ValuesChanged();
}

void PortableSettings::Load()
{
    internalLoad(settingsInstance());
}

void PortableSettings::Save()
{
    internalSave(settingsInstance());
}

void PortableSettings::SaveToFile(const QString &filepath)
{
    QSettings settings(filepath, QSettings::IniFormat);
    internalSave(&settings);
}

void PortableSettings::internalLoad(QSettings *settings)
{
    m_boolOption = settings->value("BoolOption", false).toBool();
    m_choiceOption = settings->value("ChoiceOption", QString()).toString();
    m_textOption = settings->value("TextOption", QString()).toString();
    m_integerOption = settings->value("IntegerOption", 0).toInt();
    emit ValuesChanged();
}

void PortableSettings::internalSave(QSettings *settings)
{
    settings->setValue("BoolOption", m_boolOption);
    settings->setValue("ChoiceOption", m_choiceOption);
    settings->setValue("TextOption", m_textOption);
    settings->setValue("IntegerOption", m_integerOption);
    settings->sync();
}

QString PortableSettings::portableConfigFile() const
{
    return m_portableConfigFile;
}

void PortableSettings::setPortableConfigFile(const QString &portableConfigFile)
{
    if (m_portableConfigFile != portableConfigFile) {
        resetSettings();
    }
    m_portableConfigFile = portableConfigFile;
}

void PortableSettings::setStandardPortableConfigFile()
{
    QFileInfo infoA(QCoreApplication::applicationFilePath());
    QFileInfo infoC(infoA.absoluteDir(), infoA.baseName() + ".conf");
    setPortableConfigFile(infoC.absoluteFilePath());
}

int PortableSettings::integerOption() const
{
    return m_integerOption;
}

void PortableSettings::setIntegerOption(int integerOption)
{
    m_integerOption = integerOption;
}

QString PortableSettings::textOption() const
{
    return m_textOption;
}

void PortableSettings::setTextOption(const QString &textOption)
{
    m_textOption = textOption;
}

QString PortableSettings::choiceOption() const
{
    return m_choiceOption;
}

void PortableSettings::setChoiceOption(const QString &choiceOption)
{
    m_choiceOption = choiceOption;
}

bool PortableSettings::boolOption() const
{
    return m_boolOption;
}

void PortableSettings::setBoolOption(bool boolOption)
{
    m_boolOption = boolOption;
}
