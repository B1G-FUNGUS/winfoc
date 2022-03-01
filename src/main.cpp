#include <QApplication>
#include "window.h"
#include "uniqueloggername.h"
using namespace std;

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	
	logOut("Before Window\n");

	Window::createStatWin();	

	logOut("After Window\n");

	return app.exec();
}
