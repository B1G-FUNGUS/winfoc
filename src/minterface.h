#ifndef MINTERFACE_H
#define MINTERFACE_H

#include <vector>
#include <wstring>
#include <functional>
#include <windows.h>
using namespace std;

class Minterface {
	public:
		static vector<wstring> *winStrList;
		static vector<HWND> *winIdList;
		static HWND idToCheck;
		static void setLists(vector<wstring> *strList, 
			vector<HWND> *idList);	
		static void addWins();
		static void startChecker(HWND hWnd, 
			function<void(bool, bool)> *aCheckFunc);
		static void setIdToCheck(HWND hWnd);
		static long getTime();
	private:
		static BOOL CALLBACK winToList(HWND hWnd, LPARAM lParam);
		static LRESULT CALLBACK focCheck(int nCode, WPARAM wParam, 
			LPARAM lParam);
		static function<void(bool, bool)> *checkFunc;
}

#endif
