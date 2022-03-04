#include <QApplication>
#include "window.h"
using namespace std;

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	
	Window::createStatWin(); 
	//TODO move 'organs' of window.cpp to main, then pass necessary
	//functions through pointers so that QT can be switched out for lighteri	// library

	return app.exec();
}
