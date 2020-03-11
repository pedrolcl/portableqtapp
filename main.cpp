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

#include <QCommandLineParser>
#include <QApplication>
#include <QSettings>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("MyApps");
    QCoreApplication::setApplicationName("PortableQtApp");
    QCoreApplication::setApplicationVersion("1.1.1");
    QCommandLineParser parser;
    parser.setApplicationDescription(
        QString("%1 v.%2\n\n%3")
        .arg(QCoreApplication::applicationName())
        .arg(QCoreApplication::applicationVersion())
        .arg("Copyright (C) 2018-2020 Pedro López-Cabanillas\n"
             "This program comes with ABSOLUTELY NO WARRANTY;\n"
             "This is free software, and you are welcome to redistribute it\n"
             "under certain conditions; see the LICENSE file for details.")
    );
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption portableOption({"p", "portable"}, "Portable settings format (.ini)");
    parser.addOption(portableOption);
    parser.process(app);

    MainWindow w;
    if (parser.isSet(portableOption)) {
        w.setPortableConfig();
    } else {
        QSettings::setDefaultFormat(QSettings::NativeFormat);
    }
    w.show();
    return app.exec();
}
