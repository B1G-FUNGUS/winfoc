#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget> // is this necessary?
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

class QPushButton;
class QComboBox;
class QLabel;
class Window: public QWidget {
	Q_OBJECT
	public:
		static void createStatWin();
		explicit Window(QWidget *parent = 0); //TODO could be private
		static void updateStatWinTime(bool becomesFoc, 
			bool becomesUnfoc);
	private:
		static long focStartTime;
		static int ellapsedTime;
		HWND winId;
		vector<wchar_t*> *titleList;
		vector<HWND> *hWndList;
		static Window *statWin;
		QLabel *information;
		QPushButton *start_button;
		QPushButton *refresh_button;
		QComboBox *selection;
		QLabel *focTimeLabel;
	private slots:
		void startTiming();
		void updateList();
};

#endif 
