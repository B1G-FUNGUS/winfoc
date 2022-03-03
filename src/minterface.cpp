#include <vector>
#include <utility>
#include <functional>
#include <windows.h>
#include "minterface.h"
#include "mymacros.h"
using namespace std;

HWND Minterface::idToCheck;
function<void(bool,bool)> Minterface::checkFunc;

BOOL CALLBACK Minterface::winToList(HWND hWnd, LPARAM lParam) {
	WINLIST *winList = reinterpret_cast<WINLIST*>(lParam); //TODO look out for casting errors
	int length = GetWindowTextLength(hWnd);
	if(length != 0 && IsWindowVisible(hWnd) == TRUE) {
		winList->push_back(make_pair(hWnd, new wchar_t[length + 1]));
		GetWindowText(hWnd, winList->at(winList->size() - 1).second, length + 1); //TODO look out for memory errors or other issue
	}
	return TRUE;
}

void Minterface::updateWins(WINLIST *winList) {
	winList->clear();
	EnumWindows(winToList, reinterpret_cast<LPARAM>(winList)); //TODO look out for casting errors
}

LRESULT CALLBACK Minterface::focCheck(int nCode, WPARAM wParam, LPARAM lParam) {
	bool foc = false, unfoc = false;
	if(nCode == HCBT_SETFOCUS) {
		if((HWND)wParam == idToCheck) foc = true; //TODO look out for casting errors
		if((HWND)lParam == idToCheck) unfoc = true; //TODO look out for casting errors
	}
	checkFunc(foc, unfoc);
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void Minterface::startChecker(HWND hWnd, function<void(bool,bool)> inFunc) {
	checkFunc = inFunc;
	idToCheck = hWnd;
	SetWindowsHookExA(WH_CBT, focCheck, NULL, NULL);
}
