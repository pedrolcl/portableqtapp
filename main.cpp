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

#include "mainwindow.h"
#include <QCommandLineParser>
#include <QApplication>
#include <QFileInfo>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("MyApps");
    QCoreApplication::setApplicationName("PortableQtApp template");
    QCoreApplication::setApplicationVersion("1.0.0");
    QCommandLineParser parser;
    parser.setApplicationDescription(
        QString("%1 v.%2\n\n%3")
        .arg(QCoreApplication::applicationName())
        .arg(QCoreApplication::applicationVersion())
        .arg("Copyright (C) 2018 Pedro López-Cabanillas\n"
             "This program comes with ABSOLUTELY NO WARRANTY;\n"
             "This is free software, and you are welcome to redistribute it\n"
             "under certain conditions; see the LICENSE file for details.")
    );
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption configFileOption(QStringList() << "c" << "config", "A configuration file for portable use", "configFile");
    parser.addOption(configFileOption);
    QCommandLineOption nativeOption(QStringList() << "n" << "native", "Native settings format (not portable)");
    parser.addOption(nativeOption);
    parser.process(app);

    MainWindow w;
    if (parser.isSet(configFileOption)) {
        w.setPortableConfig(parser.value(configFileOption));
    } else if (!parser.isSet(nativeOption)) {
        QFileInfo infoA(QCoreApplication::applicationFilePath());
        QFileInfo infoC(infoA.absoluteDir(), infoA.baseName() + ".conf");
        w.setPortableConfig(infoC.absoluteFilePath());
    }
    w.show();
    return app.exec();
}
