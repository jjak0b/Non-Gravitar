#include <iostream>
#include <ctime>
#include <conio.h>

// dipendenti da SO
#ifdef __WIN32__
#include <Windows.h>
// definizioni di flags per terminale windows
// fonte: www.docs.microsoft.com
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#ifndef DISABLE_NEWLINE_AUTO_RETURN
#define DISABLE_NEWLINE_AUTO_RETURN 0x0008
#endif
#else
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#endif

#include "GameConfig.h" // costanti e configurazioni del gioco

#include <cmath> // così definisco le costanti per tutto il resto del programma con _USE_MATH_DEFINES

#include "GameEngine.hpp"

char getInput(){
	char c = '\0';
	c = _getch();
	if( c == '\e' || c == INPUT_CODE_KEY_PREARROW ){  // se il carattere è il carattere di escape o di pre freccia
		if( c == '\e' ){
			_getch(); // salto il carattere [
		}
		c = _getch(); // memorizzo il carattere che identifica il tipo della freccia
		switch (c) { // the real value
			case INPUT_CODE_ESC_KEY_UP:
			case INPUT_CODE_KEY_UP:
				c = INPUT_MOVE_UP;
				break;
			case INPUT_CODE_ESC_KEY_DOWN:
			case INPUT_CODE_KEY_DOWN:
				c = INPUT_MOVE_DOWN;
				break;
			case INPUT_CODE_ESC_KEY_RIGHT:
			case INPUT_CODE_KEY_RIGHT:
				c = INPUT_MOVE_RIGHT;
				break;
			case INPUT_CODE_ESC_KEY_LEFT:
			case INPUT_CODE_KEY_LEFT:
				c = INPUT_MOVE_LEFT;
				break;
		}
	}
	return c;
}

void setCursor( int x, int y ){
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
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		return Point2D( w.ws_col, w.ws_row );
	#endif
}

void ClearScreen(){
	#ifdef __WIN32__
	system( "cls");
	#else
	system( "CLEAR");
	#endif
}

#include <cstring>
#include "Color.hpp"

int main(){
	#ifdef __WIN32__
	if( OsSupportAnsiEscape() ){
		HANDLE hOut= GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hOut, &mode);
		mode = mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING; // aggiungo flag per abilitare supporto ANSI
		SetConsoleMode(hOut, mode);
	}
	#endif

	bool b_keep_playing = true;
	double dtime = 0.0;
	char key = '\0';
	bool b_windowSizeUpdated = false;
	clock_t current_time = clock(), last_frame_time = current_time;
	Point2D screen_size = Point2D( 1, 1);
	ClearScreen();

	// screen_size.SetX( 120 );
	// screen_size.SetY( 30 );
	srand( time( 0 ) );// inizializzo generatori pseudocasuali
	GameEngine engine = GameEngine( screen_size.GetX(), screen_size.GetY() );
	do{
		setCursor( 0, 0 );
		if( _kbhit() ){
			key = getInput();
		}
		current_time = clock();
		dtime = double( current_time - last_frame_time ) / CLOCKS_PER_SEC;
		if( dtime >= FRAME_TIME ){
			last_frame_time = clock();
			screen_size = GetTerminalSize();
			#ifdef DEBUG
			screen_size.SetY( screen_size.GetY() - 5 );
			#endif
			b_windowSizeUpdated = engine.update( dtime, key, screen_size.GetX(), screen_size.GetY() );
			if( b_windowSizeUpdated ){
				ClearScreen();
			}
			b_keep_playing = engine.frame( dtime );
			key = '\0';
#ifdef DEBUG  // DEBUG
			std::cout << "Window: "<<screen_size.GetX() << "x" << screen_size.GetY() << " Duration: " << dtime << "\tFPS: ~" << round( 1.0 / dtime ) << "\tScreen size Updated: "<< b_windowSizeUpdated << std::endl;
#endif
		}
	}while( b_keep_playing );

	system( "pause" );
	return 0;
}