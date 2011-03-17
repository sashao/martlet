ABOUT
Crossplatform Remote Process Communication implementation for C++ Qt.
It can be perfectly used for local applications communication 1-to-1.
Communication may be easilly established between applications on different network hosts
scince library uses sockets for data transmission.


LICENSE
LGPL - GNU LESSER GENERAL PUBLIC LICENSE
http://www.gnu.org/copyleft/lesser.html



BUILD INSTRUCTIONS:

Make sure that you uncommented right configuration line in confir.pri file

"CONFIG+=GCC"  - known to work on linux gcc and in Qt-SDK(mingw) configuration.
"CONFIG+=MSVC" - for building using visual studio tools.

You can build this project as a normal qt project
% qmake
% make

To generate project file for Visual Studio run "qmake -tp vc"


DEPENDENCIES
Qt + compiler

Tested with Qt version 4.7.0. Should be compartible with other's.

AUTHORS
 Oleksandr Omelchuk <sashao at e-mail.ua>
