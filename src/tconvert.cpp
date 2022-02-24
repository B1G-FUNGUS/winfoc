#include "tconvert.h"
#include <iostream>
#include <string>
using namespace std;

string &tconvert(int secs, string &outString) {
	int mins = 0, hours = 0, days = 0;
	if(secs >= 2147483647) exit(1); // prevent 32 bit overflow errors
	string mtime = "";

	mtime = to_string(secs % 60) + "s" + mtime;
	if(secs >= 60) {
		mins = secs / 60;
		mtime = to_string(mins % 60) + "m " + mtime;
	}
	if(mins > 60) {
		hours = mins / 60;
		mtime = to_string(hours % 24) + "h " + mtime;
	}
	if(hours > 24) {
		days = hours / 24;
		mtime = to_string(days) + "d " + mtime;
	}

	outString = mtime;
	return outString;
}
