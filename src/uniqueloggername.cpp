#include <fstream>
#include <string>
#include <codecvt>
#include "uniqueloggername.h"
using namespace std;

void logOut(string text) {
	ofstream logStream;
	logStream.open("log.txt", ofstream::app);
	logStream << text;
	logStream.close();
}

void logOut(wchar_t* text) {
	wofstream logStream;
	logStream.open("log.txt", wofstream::app);
	std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
	logStream.imbue(loc);
	logStream << text;
	logStream.close();
}
