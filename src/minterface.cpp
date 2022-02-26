#include <vector>
#include <wstring>
#include <functional>
#include <windows.h>
#include "minterface.h"
using namespace std;

static void Minterface::setLists(vector<wstring> *strList, vector<HWND> *idList) {
	winStrList = strList;
	winIdList = idList;
}

static BOOL CALLBACK Minterface::winToList(HWND hWnd, LPARAM lParam) {
	if(GetWindowTextLength(hWnd) != 0 && IsWindowVisible(hWnd) {
		wstring winTitle;
		GetWindowText(hWnd, winTitle, 100);
		winStrList.push_back(winTitle);	
		winIdList.push_back(hWnd);
	}
	return TRUE;
}

static void Minterface::addWins() {
	winStrList.clear();
	winIdList.clear();
	EnumWindows(winToList, NULL);
}

static LRESULT CALLBACK focCheck(int nCode, WPARAM, wParam, LPARAM lParam) {
	if(ncode == HCBT_SETFOCUS) {
		bool foc = false, unfoc = false;
		if(wParam == idToCheck) foc = true;
		if(lParam == idToCheck) unfoc = true;
	}
	checkFunc(foc, unfoc);
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

static void startChecker(HWND hWn, function<void(bool, bool)> *aCheckFunc) {
	checkFunc = aCheckFunc;
	HHOOK SetWindowsHookExA(WH_CBT, focCheck, NULL, NULL);
}

static void setIdToCheck(HWND hWnd) {
	idToCheck = hWnd;
}

static int getTime() {
	PLARGE_INTEGER *time;
	NtQuerySystemTime(time);
	return (long)time;
}
