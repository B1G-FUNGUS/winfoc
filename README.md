# winfoc v1.0

Welcome to **winfoc**, an open source program to track how long a window has been focused for.

The binary can be found in the "release" folder in the form of a ".exe" file.
It should work with Windows 7 or above.

The source code can be found in the "src" folder.
If you are on Windows, you can use the Qt IDE to compile the code.
If you are on linux, you can use M Cross Environment (https://github.com/mxe/mxe) to compile it for Windows.
You can find an in-depth tutorial on (https://mxe.cc/#tutorial), but here are the basic steps:

1. Make sure you have all the required packages installed (the list can be found on (https://mxe.cc/#requirements))
2. Clone the repository with `git clone https://github.com/mxe/mxe`
3. Go into the directory with `cd mxe`
4. Run `make qtbase` to build the libraries
5. Go into your source directory
6. Add the mxe tools to your path with `export PATH=/<path-to-mxe>/usr/bin:$PATH`
7. Run mxe's version of qmake with `<path-to-mxe>/usr/i686-w64-mingw32.static/qt5/bin/qmake`
8. Run `make`
9. The executable can be found as `src/release/winfoc.exe`
