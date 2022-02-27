#include <vector>
#include <string>
#include <functional>
#include <windows.h>
#include <winternl.h>
#include "minterface.h"
using namespace std;

void Minterface::setLists(vector<wstring> *strList, vector<HWND> *idList) {
	winStrList = strList;
	winIdList = idList;
}

BOOL CALLBACK Minterface::winToList(HWND hWnd, LPARAM lParam) {
	if(GetWindowTextLength(hWnd) != 0 && IsWindowVisible(hWnd)) {
		wchar_t *titleArray; //TODO use wchar_t's elsewhere too maybe
		GetWindowText(hWnd, titleArray, 100);
		wstring winTitle(titleArray);
		winStrList->push_back(winTitle);	
		winIdList->push_back(hWnd);
	}
	return TRUE;
}

void Minterface::updateWins() {
	winStrList->clear();
	winIdList->clear();
	EnumWindows(winToList, NULL);
}

LRESULT CALLBACK Minterface::focCheck(int nCode, WPARAM wParam, LPARAM lParam) {
	bool foc = false, unfoc = false;
	if(nCode == HCBT_SETFOCUS) {
		HWND wHWnd = (HWND)wParam;
		HWND lHWnd = (HWND)lParam;
		if(wHWnd == idToCheck) foc = true;
		if(lHWnd == idToCheck) unfoc = true;
	}
	checkFunc(foc, unfoc);
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void Minterface::startChecker(HWND hWnd, void (*inFunc)(bool,bool)) {
	checkFunc = inFunc;
	idToCheck = hWnd;
	SetWindowsHookExA(WH_CBT, focCheck, NULL, NULL);
}

long Minterface::getTime() {
	LARGE_INTEGER *time;
	NtQuerySystemTime(time);
	return (long)time;
}
