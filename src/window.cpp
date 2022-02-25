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
	focTimeLabel->setGeometry(QRect(30, 10, 480, 20));
	focTimeLabel->hide();

	selection = new QComboBox(this);
	selection->setGeometry(10, 30, 270, 30);

	start_button = new QPushButton("Start", this);
	start_button->setGeometry(10, 65, 70, 30);

	connect(start_button, SIGNAL (clicked()), this, SLOT (startTiming()));
}

void Window::addWin(QString winTitle) {
	selection->addItem(winTitle);	
}

void Window::addID(vector<HWND> ids) {
	idList = ids;
}

void Window::startTiming() {
	QString winName = selection->currentText();
	if(winName.length() > 30) {
		winName.truncate(27);
		winName.append("...");
	}
	baseText = winName + " has been focused for ";
	information->setText(baseText);
	start_button->hide();
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
