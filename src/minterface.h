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
			function<void(bool,bool)> inFunc);
	private:
		static BOOL CALLBACK winToList(HWND hWnd, LPARAM lParam);
		static LRESULT CALLBACK focCheck(int nCode, WPARAM wParam, 
			LPARAM lParam);
		static function<void(bool,bool)> checkFunc; //pointer?
		static HWND idToCheck;
};

#endif
