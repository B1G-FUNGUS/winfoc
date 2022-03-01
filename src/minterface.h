#ifndef MINTERFACE_H
#define MINTERFACE_H

#include <vector>
#include <string>
#include <windows.h>
#include <functional>
using namespace std;

class Minterface {
	public:
		static vector<wchar_t*> *winStrList;
		static vector<HWND> *winIdList;
		static HWND idToCheck;
		static void setLists(vector<wchar_t*> *strList, 
			vector<HWND> *idList);	
		static void updateWins();
		static void startChecker(HWND hWnd, 
			function<void(bool,bool)> inFunc);
		// static long getTime();
	private:
		static BOOL CALLBACK winToList(HWND hWnd, LPARAM lParam);
		static LRESULT CALLBACK focCheck(int nCode, WPARAM wParam, 
			LPARAM lParam);
		// static void (*checkFunc)(bool,bool);
		static function<void(bool,bool)> checkFunc; //pointer?

};

#endif
