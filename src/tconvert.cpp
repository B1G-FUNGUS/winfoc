#include "tconvert.h"
#include <string>
using namespace std;

void tconvert(int secs, string &outString) {
	int mins = 0, hours = 0, days = 0;
	//TODO deal with overflow errors

	string mtime = to_string(secs % 60) + "s"; //TODO better way to do this? 	// Maybe with format strings?
	if(secs >= 60) {
		mins = secs / 60;
		mtime = to_string(mins % 60) + "m " + mtime;
	}
	if(mins >= 60) {
		hours = mins / 60;
		mtime = to_string(hours % 24) + "h " + mtime;
	}
	if(hours >= 24) {
		days = hours / 24;
		mtime = to_string(days) + "d " + mtime;
	}

	outString = mtime;
}
