# PortableQtApp template
# Copyright (C) 2018-2020 Pedro Lopez-Cabanillas <plcl@users.sf.net>
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

TARGET = PortableQtApp
TEMPLATE = app
QT += core gui widgets
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settings.cpp \
    settingsdialog.cpp \
    portablesettings.cpp

HEADERS += \
    mainwindow.h \
    settings.h \
    settingsdialog.h \
    portablesettings.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui
