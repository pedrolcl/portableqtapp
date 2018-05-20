Portable Qt Application Proof of Concept
========================================

This repository contains a simple _proof of concept_ Qt GUI app that may be
used as a model to build a portable real application.

Portable application is a concept explained in this [Wikipedia article](https://en.wikipedia.org/wiki/Portable_application).

> A portable application (portable app), sometimes also called standalone,
> is a program designed to read and write its configuration settings into
> an accessible folder in the computer, usually the folder where the
> portable application can be found. This makes it easier to transfer the
> program with the user's preferences and data between different computers.

For an application to be truly portable, Qt style settings need to be forced
to use the [INI file format](http://doc.qt.io/qt-5/qsettings.html#Format-enum)
instead of the native style, and the users should be able to load and save the
settings to a file name and place of their choice.

A PortableSettings class is provided, implementing a [Singleton pattern](https://en.wikipedia.org/wiki/Singleton_pattern),
hosting all the program's settings as properties, and providing methods to read and save its properties from and to
native storage and also INI files.

Using the sample
----------------

The program accepts two command line arguments:

-c fileName         Save and load settings from this file name

-n                  Save and load settings from native storage (not portable)

If no arguments are provided, a settings file name with the same name as the program and
a ".config" file name suffix is used, loated at the same directory of the executable.

The GUI also provides a menu option to export the settings to an INI file, and a dialog
box to edit the settings.

License
-------

Portable Qt App Template
Copyright (C) 2018 Pedro López-Cabanillas.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
