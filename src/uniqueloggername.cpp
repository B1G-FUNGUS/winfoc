#include <fstream>
#include "uniqueloggername.h"
using namespace std;

void logOut(string text) {
	ofstream logStream;
	logStream.open("log.txt", ofstream::out);
	logStream << text;
	logStream.close();
}
