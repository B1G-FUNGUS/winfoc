#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QLabel>
#include <QRect>
#include <QTimer>
#include <string>
#include <vector>
#include <wstring>
#include <windows.h>
#include "window.h"
#include "tconvert.h"
#include "minterface.h"
using namespace std;

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
	Minterface::setLists(titleList, hWndList);
	Minterface::updateWins();
	for(int i = 0; i < titleList.size(); i++) {
		selection->addItem(QString::fromStdWString(titleList[i]);
	}

	start_button = new QPushButton("Start", this);
	start_button->setGeometry(10, 65, 70, 30);

	refresh_button = new QPushButton("Refresh", this);
	refresh_button->setGeometry(80, 65, 98, 30);

	connect(start_button, SIGNAL (clicked()), this, SLOT (startTiming()));
	connect(refresh_button, SIGNAL (clicked()), this, SLOT (updateList()));
}

static void createStatWin() {
	statWin = new Window();
}

static void updateStatWinTime(bool becomesFoc, bool becomesUnfoc) {
	// may cause minor error if window is already focused
	if(becomesFoc) {
		focStartTime = Minterface::getTime();
	}
	if becomesUnfoc {
		ellapsedTime += Minterface::getTime() - focStartTime;
		statWin->focTimeLabel->setText(tconvert(ellapsedTime));
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

	winId = hWndList[selection->currentIndex()];
	ellapsedTime = 0;
	focStarTime = Minterface::getTime();
	Minterface::startChecker(winId, &updateStatWinTime);
	// realID = GetWindowThreadProcessId(id, NULL);
}

void Window::updateList() {
	selection->clear();
	Minterface::updateWins();
	for(int i = 0; i < titleList.size(); i++) {
		selection->addItem(QString::fromStdWString(titleList[i]);
	}
}
