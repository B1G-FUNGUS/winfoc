#include <vector>
#include <string>
#include <functional>
#include <string>
#include <windows.h>
#include <winternl.h>
#include "minterface.h"
#include "uniqueloggername.h"
using namespace std;

vector<wchar_t*> *Minterface::winStrList;
vector<HWND> *Minterface::winIdList;
HWND Minterface::idToCheck;
function<void(bool,bool)> Minterface::checkFunc;

void Minterface::setLists(vector<wchar_t*> *strList, vector<HWND> *idList) {
	logOut("Before set lists\n");
	winStrList = strList;
	winIdList = idList;
	logOut("After set lists\n");
}

BOOL CALLBACK Minterface::winToList(HWND hWnd, LPARAM lParam) {
	logOut("Before win to list\n");
	if(GetWindowTextLength(hWnd) != 0 && IsWindowVisible(hWnd) == TRUE) {
	// if(true) {
		logOut("LOG1 LOG1 LOG1 LOG1");
		wchar_t titleArray[GetWindowTextLength(hWnd)+1];  //TODO imrpove
		logOut("LOG2 LOG2 LOG2 LOG2");
		GetWindowText(hWnd, titleArray, 100); //TODO may error
		logOut("LOG3 LOG3 LOG3 LOG3");
		// wstring winTitle = (wstring)titleArray;
		logOut("Test test test test test\n");
		winStrList->push_back(titleArray);	
		logOut("LOG4 LOG4 LOG4 LOG4");
		winIdList->push_back(hWnd);
	}
	return TRUE;
	logOut("After win to list\n");
}

void Minterface::updateWins() {
	logOut("Before update wins\n");
	winStrList->clear(); //TODO error here
	logOut("eiurweirewyrweiryewruweyriweyrewiuryweur");
	winIdList->clear();
	logOut("34234324324923432043294238492034934293042");
	EnumWindows(winToList, NULL);
	logOut("After update wins\n");
}

LRESULT CALLBACK Minterface::focCheck(int nCode, WPARAM wParam, LPARAM lParam) {
	logOut("Before foc check\n");
	bool foc = false, unfoc = false;
	if(nCode == HCBT_SETFOCUS) {
		HWND wHWnd = (HWND)wParam;
		HWND lHWnd = (HWND)lParam;
		if(wHWnd == idToCheck) foc = true;
		if(lHWnd == idToCheck) unfoc = true;
		// logOut("IDs:\n");
		// logOut((long)idToCheck + ",");
		// logOut((long)wHWnd + ",");
		// logOut((long)lHWnd + "\n");
	}
	checkFunc(foc, unfoc);
	return CallNextHookEx(NULL, nCode, wParam, lParam);
	logOut("After foc checkn\n");
}

void Minterface::startChecker(HWND hWnd, function<void(bool,bool)> inFunc) {
	logOut("Before start of checker\n");
	checkFunc = inFunc;
	idToCheck = hWnd;
	SetWindowsHookExA(WH_CBT, focCheck, NULL, NULL);
	logOut("After start of checker\n");
}

/*long Minterface::getTime() {
	LARGE_INTEGER *time;
	NtQuerySystemTime(time);
	return (long)time;
}*/
