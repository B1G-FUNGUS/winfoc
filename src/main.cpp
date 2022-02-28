#include <QApplication>
#include "window.h"
using namespace std;

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	Window::createStatWin();	

	return app.exec();
}
