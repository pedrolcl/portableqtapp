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

#include <QPushButton>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "portablesettings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::RestoreDefaults),
            &QPushButton::clicked,this, &SettingsDialog::restoreDefaults);
    connect(this, &QDialog::finished, this, &SettingsDialog::closing);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::restoreDefaults()
{
    PortableSettings::instance()->ResetDefaults();
    refreshDialog();
}

void SettingsDialog::refreshDialog()
{
    ui->checkOption->setChecked(PortableSettings::instance()->boolOption());
    ui->comboOption->setCurrentText(PortableSettings::instance()->choiceOption());
    ui->textOption->setText(PortableSettings::instance()->textOption());
    ui->numberOption->setValue(PortableSettings::instance()->integerOption());
}

void SettingsDialog::storeSettings()
{
    PortableSettings::instance()->setBoolOption(ui->checkOption->isChecked());
    PortableSettings::instance()->setChoiceOption(ui->comboOption->currentText());
    PortableSettings::instance()->setTextOption(ui->textOption->text());
    PortableSettings::instance()->setIntegerOption(ui->numberOption->value());
}

void SettingsDialog::showEvent(QShowEvent *ev)
{
    refreshDialog();
    QDialog::showEvent(ev);
}

void SettingsDialog::closing(int result)
{
    if (result == QDialog::Accepted)
        storeSettings();
}
