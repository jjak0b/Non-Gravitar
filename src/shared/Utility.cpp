#include "Utility.h"
#include <string>

#ifdef __WIN32__
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace Utility {
	bool CheckEqualsOrSubstring(const char *str, const char *str_or_substr, bool check_as_subString) {
		bool isMatching = false;
		std::string o_str = std::string(str);
		if (str != NULL) {
			if (!check_as_subString) {
				isMatching = !o_str.compare(str_or_substr);
			}
			else {
				isMatching = o_str.rfind(str_or_substr) != o_str.npos;
			}
		}
		o_str.clear();
		return isMatching;
	}

	std::list<Point2D>::iterator random_element(std::list<Point2D>::iterator begin, std::list<Point2D>::iterator end) {

		unsigned long n = std::distance(begin, end);
		unsigned long divisor = (RAND_MAX + 1) / n;

		unsigned long k;
		do {
			k = std::rand() / divisor;
		} while (k >= n);

		std::advance(begin, k);
		return begin;
	}

	void sleep( unsigned int milliseconds ) {
#ifdef __WIN32__
		Sleep(milliseconds);
#else
		usleep(milliseconds * 1000); // richiede microsecondi
#endif

	}

	namespace GUI {

		void ClearScreen(){
#ifdef __WIN32__
			system( "cls");
#else
			system( "CLEAR");
#endif
		}

		namespace Terminal {

			void SetTerminalCursor(int x, int y){
#ifdef __WIN32__
				HANDLE hOut;
				COORD Position;

				hOut = GetStdHandle(STD_OUTPUT_HANDLE);

				Position.X = x;
				Position.Y = y;
				SetConsoleCursorPosition(hOut, Position);
#else
				cout << "\e[" << y << ";" << x << "H");
#endif
			}

			Point2D GetTerminalSize(){
#ifdef __WIN32__
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				int columns, rows;
				HANDLE hOut;
				hOut = GetStdHandle(STD_OUTPUT_HANDLE);
				GetConsoleScreenBufferInfo( hOut, &csbi);
				columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
				rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
				return Point2D( columns, rows );
#else
				// WARNING: non testato
				struct winsize w;
				ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
				return Point2D( w.ws_col, w.ws_row );
#endif
			}

		}
	}
}