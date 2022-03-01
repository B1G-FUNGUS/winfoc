#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QLabel>
#include <QRect>
#include <string>
#include <vector>
#include <string>
#include <ctime>
#include <windows.h>
#include "window.h"
#include "tconvert.h"
#include "minterface.h"
// #include "log.h"
#include "uniqueloggername.h"
using namespace std;

int Window::ellapsedTime;
long Window::focStartTime;
Window *Window::statWin;

Window::Window(QWidget *parent): QWidget(parent) {
	logOut("Before Window Constructor\n");

	setFixedSize(500, 105);

	information = new QLabel("Pick the window you want to track.", this);
	information->setGeometry(QRect(10, 10, 480, 20));

	focTimeLabel = new QLabel(this);
	focTimeLabel->setGeometry(QRect(10, 30, 480, 20));
	focTimeLabel->setStyleSheet("font-weight: bold");
	focTimeLabel->hide();

	selection = new QComboBox(this);
	selection->setGeometry(10, 30, 270, 30);
	titleList = new vector<wchar_t*>;
	hWndList = new vector<HWND>;
	logOut("Before setting lists");
	Minterface::setLists(titleList, hWndList);
	logOut("Before updating lists");
	this->updateList();

	start_button = new QPushButton("Start", this);
	start_button->setGeometry(10, 65, 70, 30);

	refresh_button = new QPushButton("Refresh", this);
	refresh_button->setGeometry(80, 65, 98, 30);

	connect(start_button, SIGNAL (clicked()), this, SLOT (startTiming()));
	connect(refresh_button, SIGNAL (clicked()), this, SLOT (updateList()));

	this->show();
	logOut("After Window Constructor\n");
}

void Window::createStatWin() {
	logOut("Before Stat Win Creation\n");
	statWin = new Window;
	logOut("After Stat Win Creation\n");
}

void Window::updateStatWinTime(bool becomesFoc, bool becomesUnfoc) {
	logOut("Before time update\n");
	//TODO may cause minor error if window is already focused
	if(becomesFoc) {
		// focStartTime = Minterface::getTime();
		focStartTime = (long)time(0);
	}
	if(becomesUnfoc) {
		ellapsedTime += (long)time(0) - focStartTime;
		string tstring;
		tconvert(ellapsedTime, tstring);
		statWin->focTimeLabel->setText(QString::fromStdString(tstring));
	}
	logOut("After time update\n");
}

void Window::startTiming() {
	logOut("Before timing start\n");
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
	
	winId = hWndList->at(selection->currentIndex());
	ellapsedTime = 0;
	focStartTime = (long)time(0);
	Minterface::startChecker(winId, &updateStatWinTime);
	// realID = GetWindowThreadProcessId(id, NULL);
	logOut("After timing start\n");
}

void Window::updateList() {
	logOut("Before list update\n");
	selection->clear();
	Minterface::updateWins();
	for(int i = 0; i < titleList->size(); i++) {
		selection->addItem(QString::fromWCharArray(titleList->at(i)));
	}
	logOut("After list update\n");
}
