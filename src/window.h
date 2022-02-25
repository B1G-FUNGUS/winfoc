#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <windows.h>
#include <vector>
using namespace std;

class QPushButton;
class QComboBox;
class QString;
class QLabel;
class Window: public QWidget {
	Q_OBJECT
	public:
		explicit Window(QWidget *parent = 0);
		void addWin(QString winTitle);
		void addID(vector<HWND> ids);
	private:
		int time;
		HWND id;
		DWORD realID;
		QString baseText;
		vector<HWND> idList;
		QLabel *information;
		QLabel *focTimeLabel;
		QPushButton *start_button;
		QComboBox *selection;
	private slots:
		void startTiming();
		void timerCheck();
};

#endif 
