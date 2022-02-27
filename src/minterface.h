#ifndef MINTERFACE_H
#define MINTERFACE_H

#include <vector>
#include <string>
// #include <functional>
#include <windows.h>
using namespace std;

class Minterface {
	public:
		static vector<wstring> *winStrList;
		static vector<HWND> *winIdList;
		static HWND idToCheck;
		static void setLists(vector<wstring> *strList, 
			vector<HWND> *idList);	
		static void updateWins();
		static void startChecker(HWND hWnd, 
			void (*inFunc)(bool, bool));
		static long getTime();
	private:
		static BOOL CALLBACK winToList(HWND hWnd, LPARAM lParam);
		static LRESULT CALLBACK focCheck(int nCode, WPARAM wParam, 
			LPARAM lParam);
		static void (*checkFunc)(bool,bool);
};

#endif
