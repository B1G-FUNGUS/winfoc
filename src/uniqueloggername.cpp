#include <fstream>
#include <string>
#include <codecvt> 
#include "uniqueloggername.h"
using namespace std;

//TODO in general I feel like this could be made better, but I'm not sure how

void logOut(string text) {
	ofstream logStream;
	logStream.open("log.txt", ofstream::app);
	logStream << text;
	logStream.close();
}

void logOut(wchar_t* text) {
	wofstream logStream;
	logStream.open("log.txt", wofstream::app);
	std::locale locale(locale::classic(), new codecvt_utf8<wchar_t>);
	logStream.imbue(locale);
	logStream << text;
	logStream.close();
}
