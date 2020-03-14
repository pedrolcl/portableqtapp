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

#include <QApplication>
#include <QFileDialog>

#if defined(Q_OS_MACOS)
#include <CoreFoundation/CoreFoundation.h>
#endif

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "portablesettings.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_portableConfig(false)
{
    ui->setupUi(this);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::editSettings);
    connect(ui->actionExportPortableConfig, &QAction::triggered, this, &MainWindow::exportSettings);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::editSettings()
{
    SettingsDialog dlg;
    dlg.exec();
}

void MainWindow::exportSettings()
{
    QFileDialog dlg(this);
    dlg.setNameFilter(tr("Configuration Files (*.config)"));
    dlg.setDirectory(qApp->applicationFilePath());
    dlg.setWindowTitle(tr("Export Portable Settings"));
    dlg.setDefaultSuffix("config");
    dlg.setFileMode(QFileDialog::AnyFile);
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    if (dlg.exec() == QDialog::Accepted) {
        QString fileName = dlg.selectedFiles().first();
        if (!fileName.isEmpty())
            PortableSettings::instance()->SaveToFile(fileName);
    }
}

void MainWindow::setPortableConfig(const QString fileName)
{
    m_portableConfig = true;
    if (fileName.isEmpty()) {
        QFileInfo appInfo(QCoreApplication::applicationFilePath());
#if defined(Q_OS_MACOS)
        CFURLRef url = static_cast<CFURLRef>(CFAutorelease(static_cast<CFURLRef>(CFBundleCopyBundleURL(CFBundleGetMainBundle()))));
        QString path = QUrl::fromCFURL(url).path() + "../";
        QFileInfo cfgInfo(path, appInfo.baseName() + ".conf");
#else
        QFileInfo cfgInfo(appInfo.absoluteDir(), appInfo.baseName() + ".conf");
#endif
        Settings::setFileName(cfgInfo.absoluteFilePath());
    } else {
        Settings::setFileName(fileName);
    }
}

void MainWindow::showEvent(QShowEvent *ev)
{
    PortableSettings::instance()->ReadSettings();
    QMainWindow::showEvent(ev);
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    PortableSettings::instance()->SaveSettings();
    QMainWindow::closeEvent(ev);
}
