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
		vector<HWND> idList;
		explicit Window(QWidget *parent = 0);
		void addWin(QString winTitle);
		void addID(vector<HWND> ids);
		static void makeWin();
	private:
		int time;
		HWND id;
		DWORD realID;
		QString baseText;
		QLabel *information;
		QLabel *focTimeLabel;
		QPushButton *start_button;
		QPushButton *refresh_button;
		QComboBox *selection;
		// BOOL CALLBACK cecondListWins(HWND hWnd, LPARAM lparam);
	private slots:
		void startTiming();
		void timerCheck();
		void updateList();
};
Window *myWin;

#endif 
