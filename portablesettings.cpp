/*
 PortableQtApp template
 Copyright (C) 2018-2020 Pedro Lopez-Cabanillas <plcl@users.sf.net>

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

#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include "portablesettings.h"
#include "settings.h"

PortableSettings::PortableSettings(QObject *parent) : QObject(parent)
{
    ResetDefaults();
}

PortableSettings* PortableSettings::instance()
{
    static PortableSettings inst;
    return &inst;
}

void PortableSettings::ResetDefaults()
{
    m_boolOption = false;
    m_choiceOption = QString();
    m_textOption = QString();
    m_integerOption = 0;
    emit ValuesChanged();
}

void PortableSettings::ReadSettings()
{
    Settings settings;
    qDebug() << Q_FUNC_INFO << settings->fileName();
    internalRead(*settings);
}

void PortableSettings::SaveSettings()
{
    Settings settings;
    qDebug() << Q_FUNC_INFO << settings->fileName();
    internalSave(*settings);
}

void PortableSettings::ReadFromFile(const QString &filepath)
{
    QSettings settings(filepath, QSettings::IniFormat);
    qDebug() << Q_FUNC_INFO << settings.fileName();
    internalRead(settings);
}

void PortableSettings::SaveToFile(const QString &filepath)
{
    QSettings settings(filepath, QSettings::IniFormat);
    qDebug() << Q_FUNC_INFO << settings.fileName();
    internalSave(settings);
}

void PortableSettings::internalRead(QSettings &settings)
{
    m_boolOption = settings.value("BoolOption", false).toBool();
    m_choiceOption = settings.value("ChoiceOption", QString()).toString();
    m_textOption = settings.value("TextOption", QString()).toString();
    m_integerOption = settings.value("IntegerOption", 0).toInt();
    emit ValuesChanged();
}

void PortableSettings::internalSave(QSettings &settings)
{
    settings.setValue("BoolOption", m_boolOption);
    settings.setValue("ChoiceOption", m_choiceOption);
    settings.setValue("TextOption", m_textOption);
    settings.setValue("IntegerOption", m_integerOption);
    settings.sync();
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
