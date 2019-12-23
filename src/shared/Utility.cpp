#include "Utility.h"
#include "engine/GameConfig.h"
#include <string>
#include <iostream>

#ifdef __WIN32__
#include <windows.h>
#include <versionhelpers.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#endif

#include <conio.h>

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
			if( Terminal::OsSupportAnsiEscape() ) {
				std::cout << "\033[2J";
			}
			else {
#ifdef __WIN32__
				system("cls");
#else
				system( "CLEAR");
#endif
			}
		}
		
		bool IsKeyPressed(){
			return _kbhit();
		}
		
		int GetKeyboardInput(){
			return _getch();
		}
		
		namespace Terminal {

			void SetTerminalCursor(int x, int y){
#ifdef __WIN32_
				HANDLE hOut;
				COORD Position;

				hOut = GetStdHandle(STD_OUTPUT_HANDLE);

				Position.X = x;
				Position.Y = y;
				SetConsoleCursorPosition(hOut, Position);
#else
				std::cout << "\e[" << y << ";" << x << "H";
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
				struct winsize w;
				ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
				return Point2D( w.ws_col, w.ws_row );
#endif
			}

			bool OsSupportAnsiEscape(){
				bool isSupported = false;

#ifdef ENABLE_ANSI_IF_SUPPORTED
#ifdef __WIN32__
				// per ora ci accontentiamo
				isSupported = IsWindows8OrGreater();
/*		// Abilitare se viene aggiunto un file manifest in modo che tale che WINDOWS API riconosca se è eseguito su windows >= 8.1
		DWORDLONG dwlConditionMask = 0;
		OSVERSIONINFOEX osVersionInfo;
		osVersionInfo.dwOSVersionInfoSize = sizeof( OSVERSIONINFOEX );
		osVersionInfo.dwMajorVersion = 6; // l'applicazione è priva di un manifest e quindi viene considerata dal sistema operativo come applicazione per windows 8 (6.2)
		osVersionInfo.dwMinorVersion = 2;
		// osVersionInfo.dwBuildNumber = 10586; // Windows 10 supporta codici Ansi escape da versione 1511 (build 10586)
		// osVersionInfo.wProductType == VER_NT_WORKSTATION
		int op = VER_GREATER_EQUAL;
		VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION, op );
		VER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION, op );
		VER_SET_CONDITION( dwlConditionMask, VER_BUILDNUMBER, op );
		isSupported = VerifyVersionInfo( &osVersionInfo, VER_MINORVERSION | VER_MAJORVERSION , dwlConditionMask );
*/
#else
				isSupported = true;
#endif
#endif
				return isSupported;
			}

		}
	}
}
