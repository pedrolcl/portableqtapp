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

#ifndef PORTABLESETTINGS_H
#define PORTABLESETTINGS_H

#include <QObject>
#include <QPointer>
#include <QString>
#include <QSettings>

class PortableSettings : public QObject
{
    Q_OBJECT

public:
    static PortableSettings* instance();
    QSettings *settingsInstance();
    void resetSettings();

    bool boolOption() const;
    void setBoolOption(bool boolOption);

    QString choiceOption() const;
    void setChoiceOption(const QString &choiceOption);

    QString textOption() const;
    void setTextOption(const QString &textOption);

    int integerOption() const;
    void setIntegerOption(int integerOption);

    QString portableConfigFile() const;
    void setPortableConfigFile(const QString &portableConfigFile);
    void setStandardPortableConfigFile();

signals:
    void ValuesChanged();

public slots:
    void ResetDefaults();
    void Load();
    void Save();
    void SaveToFile(const QString &filepath);

private:
    explicit PortableSettings(QObject *parent = nullptr);
    ~PortableSettings();

    void internalLoad(QSettings *settings);
    void internalSave(QSettings *settings);

    QPointer<QSettings> m_settings;
    QString m_portableConfigFile;
    bool    m_boolOption;
    QString m_choiceOption;
    QString m_textOption;
    int     m_integerOption;
};

#endif // PORTABLESETTINGS_H
