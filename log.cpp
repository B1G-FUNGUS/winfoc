#include "log.h"
#include <fstream>
#include <string>
using namespace std;

void logOut(string string) {
	ofstream log;
	log.open("log.txt");
	log << string << endl;
	log.close();
}
