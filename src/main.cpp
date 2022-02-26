#include <QApplication>
#include <QString>
#include <windows.h>
#include "window.h"
#include <vector>
using namespace std;

// Window *window;
vector<HWND> id;
BOOL CALLBACK listWins(HWND hWnd, LPARAM lparam);

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	// window = new Window;
	// myWin = new Window; // the program will break, fix

	EnumWindows(listWins, NULL);
	// window->addID(id);
	myWin = new Window;

	// window->show();
	myWin->show();

	return app.exec();
}

BOOL CALLBACK listWins(HWND hWnd, LPARAM lparam) {
	int length = GetWindowTextLength(hWnd);
	wchar_t title[length + 1];
	GetWindowText(hWnd, title, length + 1);
	if(IsWindowVisible(hWnd) && length != 0) {
		QString titleStr = QString::fromWCharArray(title, length + 1);
		// window->addWin(titleStr);
		myWin->addWin(titleStr);
		id.push_back(hWnd);
	}
	return TRUE;
}
