#include <QPushButton> //TODO Tons of dependencies
#include <QComboBox> //TODO notice how we don't have to include QWidget, I am being dumb
#include <QString>
#include <QLabel>
#include <QRect>
#include <vector>
#include <utility>
#include <string>
#include <ctime>
#include <windows.h> //TODO move dependent functions to minterface (or main)
#include "window.h"
#include "tconvert.h"
#include "minterface.h" //TODO move to main
#include "mymacros.h"
using namespace std;

bool Window::wasFoc; //TODO move variables and 'organs' to main, just have
// this class be the 'skin'
int Window::ellapsedTime;
long Window::focStartTime;
Window *Window::statWin;

Window::Window(QWidget *parent): QWidget(parent) {
	setFixedSize(500, 105);

	information = new QLabel("Pick the window you want to track.", this);
	information->setGeometry(QRect(10, 10, 480, 20));

	focTimeLabel = new QLabel(this);
	focTimeLabel->setGeometry(QRect(10, 30, 480, 20));
	focTimeLabel->setStyleSheet("font-weight: bold");
	focTimeLabel->hide();

	selection = new QComboBox(this);
	selection->setGeometry(10, 30, 270, 30);
	WINLIST winList; 
	this->updateList();

	start_button = new QPushButton("Start", this);
	start_button->setGeometry(10, 65, 70, 30);

	refresh_button = new QPushButton("Refresh", this);
	refresh_button->setGeometry(80, 65, 98, 30);

	connect(start_button, SIGNAL (clicked()), this, SLOT (startTiming()));
	connect(refresh_button, SIGNAL (clicked()), this, SLOT (updateList()));

	this->show();
}

void Window::createStatWin() {
	statWin = new Window;
}

void Window::updateStatWinTime(bool foc) {
	//TODO look for unexpected errors
	if(foc) {
		wasFoc = true;
		focStartTime = (long)time(0); //TODO casting
	} else if (wasFoc) {
		ellapsedTime += (long)time(0) - focStartTime; //TODO casting
		string tstring;
		tconvert(ellapsedTime, tstring);
		statWin->focTimeLabel->setText(QString::fromStdString(tstring));
		wasFoc = false;
	}
}

void Window::startTiming() {
	QString winName = selection->currentText();
	if(winName.length() > 25) {
		winName.truncate(22);
		winName.append("...");
	}
	information->setText("\"" + winName + "\"" + " has been focused for ");

	start_button->hide();
	refresh_button->hide();
	selection->hide();
	focTimeLabel->show();
	
	winId = winList.at(selection->currentIndex()).first;
	ellapsedTime = 0;
	wasFoc = (GetActiveWindow() == winId); 
	focStartTime = (long)time(0); //TODO should prevent error?
	Minterface::startChecker(winId, &updateStatWinTime); 
}

void Window::updateList() {
	selection->clear();
	Minterface::updateWins(&winList);
	for(unsigned int i = 0; i < winList.size(); i++) {
		selection->addItem(QString::fromWCharArray(winList.at(i).second));
	}
}
