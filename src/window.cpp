#include "window.h"
#include "tconvert.h"
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QLabel>
#include <QRect>
#include <vector>
#include <windows.h>
#include <QTimer>
#include <string>

using namespace std;

Window::Window(QWidget *parent): QWidget(parent) {
	time = 0;

	setFixedSize(500, 105);

	information = new QLabel("Pick the window you want to track.", this);
	information->setGeometry(QRect(10, 10, 480, 20));

	focTimeLabel = new QLabel(this);
	focTimeLabel->setGeometry(QRect(10, 30, 480, 20));
	focTimeLabel->hide();

	selection = new QComboBox(this);
	selection->setGeometry(10, 30, 270, 30);

	start_button = new QPushButton("Start", this);
	start_button->setGeometry(10, 65, 70, 30);

	refresh_button = new QPushButton("Refresh", this);
	refresh_button->setGeometry(80, 65, 98, 30);

	connect(start_button, SIGNAL (clicked()), this, SLOT (startTiming()));
	connect(refresh_button, SIGNAL (clicked()), this, SLOT (updateList()));
}

void Window::addWin(QString winTitle) {
	selection->addItem(winTitle);	
}

void Window::addID(vector<HWND> ids) {
	idList = ids;
}

void Window::startTiming() {
	QString winName = selection->currentText();
	if(winName.length() > 25) {
		winName.truncate(22);
		winName.append("...");
	}
	baseText = "\"" + winName + "\"" + " has been focused for ";
	information->setText(baseText);
	start_button->hide();
	refresh_button->hide();
	selection->hide();
	focTimeLabel->show();
	focTimeLabel->setStyleSheet("font-weight: bold");
	id = idList[selection->currentIndex()];
	realID = GetWindowThreadProcessId(id, NULL);
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, 
		QOverload<>::of(&timerCheck));
	timer->start(1000);
}

void Window::timerCheck() {
	DWORD otherAID; // WHY DOES THIS MAKE THE PROGRAM WORK??
	DWORD activeID = GetWindowThreadProcessId(GetForegroundWindow(), &otherAID);
	if(realID == activeID) { 
		time += 1;
	}
	/*QString real = QString::number(realID);
	QString active = QString::number(otherAID);
	// QString secs = QString::number(time);
	// information->setText(baseText + secs + " seconds");
	// information->setText(real + " | " + active + " | " + secs);*/
	string focTime;
	tconvert(time, focTime);
	focTimeLabel->setText(QString::fromStdString(focTime));
}

BOOL CALLBACK secondListWins(HWND hWnd, LPARAM lparam);
/*BOOL CALLBACK Window::cecondListWins(HWND hWnd, LPARAM lparam) {
	return TRUE;
};*/

void Window::updateList() {
	idList.clear();
	selection->clear();
	EnumWindows(secondListWins, (LPARAM)this); // mr. gates, why do you haveto hurt me like this?
}

BOOL CALLBACK secondListWins(HWND hWnd, LPARAM lparam) {
	int length = GetWindowTextLength(hWnd);
	wchar_t title[length + 1];
	GetWindowText(hWnd, title, length + 1);
	Window *winpoint = (Window*)lparam;
	if(IsWindowVisible(hWnd) && length != 0) {
		QString titleStr = QString::fromWCharArray(title, length + 1);
		winpoint->addWin(titleStr);
		winpoint->idList.push_back(hWnd);
	}
	return TRUE;
}
