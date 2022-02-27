#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget> // is this necessary?
#include <vector>
#include <wstring>
#include <windows.h>
using namespace std;

class QPushButton;
class QComboBox;
class QLabel;
class Window: public QWidget {
	Q_OBJECT
	public:
		static void createStatWin();
	private:
		static long focStartTime;
		static int ellapsedTime;
		HWND winId;
		vector<wstring> *titleList;
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
