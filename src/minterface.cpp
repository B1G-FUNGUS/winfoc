#include <vector>
#include <utility>
#include <functional>
#include <windows.h>
#include "minterface.h"
#include "mymacros.h"
using namespace std;

HWND Minterface::idToCheck;
function<void(bool)> Minterface::checkFunc;

BOOL CALLBACK Minterface::winToList(HWND hWnd, LPARAM lParam) {
	WINLIST *winList = reinterpret_cast<WINLIST*>(lParam); //TODO casting
	int length = GetWindowTextLength(hWnd);
	if(length != 0 && IsWindowVisible(hWnd) == TRUE) {
		winList->push_back(make_pair(hWnd, new wchar_t[length + 1]));
		GetWindowText(hWnd, winList->at(winList->size() - 1).second, 
			length + 1); //TODO memory issue?
	}
	return TRUE;
}

void Minterface::updateWins(WINLIST *winList) {
	winList->clear();
	EnumWindows(winToList, reinterpret_cast<LPARAM>(winList)); //TODO casting
}

void CALLBACK Minterface::winFocChange(HWINEVENTHOOK hook, DWORD event, HWND hWnd, LONG objId, LONG childId, DWORD eventThread, DWORD eventTime)
{
	// Note that event time is not passed as an argument because using the
	// standard time function instead makes future compatibility easier
	checkFunc((hWnd == idToCheck));
}

void Minterface::startChecker(HWND hWnd, function<void(bool)> inFunc) {
	checkFunc = inFunc;
	idToCheck = hWnd;
	HWINEVENTHOOK hook = SetWinEventHook(
		EVENT_OBJECT_FOCUS, EVENT_OBJECT_FOCUS, NULL, 
		&Minterface::winFocChange, 0, 0, 
		WINEVENT_OUTOFCONTEXT); //TODO double spew error
}
