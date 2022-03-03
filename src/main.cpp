#include <QApplication>
#include "window.h"
using namespace std;

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	
	Window::createStatWin(); //TODO make static lists instead of window?

	return app.exec();
}
