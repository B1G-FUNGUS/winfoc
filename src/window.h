#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget> // is this necessary?
// #include <windows.h>
#include <vector>
using namespace std;

class QPushButton;
class QComboBox;
class QString;
class QLabel;
class Window: public QWidget {
	Q_OBJECT
	public:
		static void createStaticWin();
	private:
		int time;
		/*HWND id;
		DWORD realID; */
		// QString baseText;
		static Window *statWin;
		QLabel *information;
		QLabel *focTimeLabel;
		QPushButton *start_button;
		QPushButton *refresh_button;
		QComboBox *selection;
		// BOOL CALLBACK cecondListWins(HWND hWnd, LPARAM lparam);
	private slots:
		void startTiming();
		// void timerCheck();
		void updateList();
};

#endif 
