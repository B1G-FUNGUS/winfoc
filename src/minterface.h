#ifndef MINTERFACE_H
#define MINTERFACE_H

#include <vector>
#include <utility>
#include <functional>
#include <windows.h>
#include "mymacros.h"
using namespace std;

class Minterface {
	public:
		static void updateWins(WINLIST *winList);
		static void startChecker(HWND hWnd, 
			function<void(bool)> inFunc);
	private:
		static BOOL CALLBACK winToList(HWND hWnd, LPARAM lParam);
		static void CALLBACK winFocChange( //TODO should it return void?
			HWINEVENTHOOK hook, DWORD event, HWND hWnd, 
			LONG objId, LONG childId, DWORD eventThread, 
			DWORD eventTime);
		static function<void(bool)> checkFunc; 
		static HWND idToCheck;
};

#endif
