#include <iostream>
#include <ctime>
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

#include "shared/Utility.h"
#include "engine/GameConfig.h" // costanti e configurazioni del gioco
#include <cmath> // così definisco le costanti per tutto il resto del programma con _USE_MATH_DEFINES
#include "engine/GameEngine.hpp"

char GetInput(){
	char c = '\0';
	c = Utility::GUI::GetKeyboardInput();
	if( c == '\e' || c == INPUT_CODE_KEY_PREARROW ){  // se il carattere è il carattere di escape o di pre freccia
		if( c == '\e' ){
			Utility::GUI::GetKeyboardInput(); // salto il carattere [
		}
		c = Utility::GUI::GetKeyboardInput(); // memorizzo il carattere che identifica il tipo della freccia
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


int main(){
	#ifdef __WIN32__
	if( Utility::GUI::Terminal::OsSupportAnsiEscape() ){
		HANDLE hOut= GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hOut, &mode);
		mode = mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING; // aggiungo flag per abilitare supporto ANSI
		SetConsoleMode(hOut, mode);
	}
	#endif

	bool
		b_keep_playing = true,
		b_windowSizeUpdated = false;
	char key = '\0';
	double
			dtime = 0.0,
			time_sleep_milliseconds = 0.0,
			time_processing_milliseconds = 0.0;
	clock_t
		current_time = clock(),
		last_frame_time = current_time;

	Point2D screen_size = Point2D( 1, 1);
	Utility::GUI::ClearScreen();

	srand( time( NULL ) );// inizializzo generatori pseudocasuali
	GameEngine engine = GameEngine( screen_size.GetX(), screen_size.GetY() );
	do{
		// attende solo se il tempo di attesa è positivo, altrimenti l'esecuzione è in ritardo ... (lag)
		if( time_sleep_milliseconds > 0.0 ) {
			Utility::sleep( time_sleep_milliseconds );
		}

		Utility::GUI::Terminal::SetTerminalCursor(0, 0);
		key = '\0';
		if( Utility::GUI::IsKeyPressed() ){
			key = GetInput();
		}
		current_time = clock();
		dtime = double( current_time - last_frame_time ) / CLOCKS_PER_SEC;
		last_frame_time = current_time;
		screen_size = Utility::GUI::Terminal::GetTerminalSize();
#ifdef DEBUG
		screen_size.SetY( screen_size.GetY() - DEBUG_TERMINAL_LINES );
#endif
		b_windowSizeUpdated = engine.update( dtime, key, screen_size.GetX(), screen_size.GetY() );
		if( b_windowSizeUpdated ){
			Utility::GUI::ClearScreen();
		}
		b_keep_playing = engine.frame( dtime );

		current_time = clock();
		// tempo computazionale richiesto in questo frame
		time_processing_milliseconds = double( current_time - last_frame_time );
		// tempo di attesa richiesto prima del prossimo frame
		time_sleep_milliseconds = ( (FRAME_TIME*CLOCKS_PER_SEC) - time_processing_milliseconds ) ;

#ifdef DEBUG  // DEBUG
		const int size_str_buffer = 150;
		char str_print_buffer[size_str_buffer] = "";
		snprintf( str_print_buffer,
				  size_str_buffer,
				  "Window: %d x %d \t Scr Updated: %d \t FPS: ~%.02f \t Frame time: %.03f \t Processing Time: %.03f \t Sleep: %.04f",
				  (int)screen_size.GetX(), (int)screen_size.GetY(), b_windowSizeUpdated, round( 1.0 / dtime ), dtime, time_processing_milliseconds / CLOCKS_PER_SEC, time_sleep_milliseconds / CLOCKS_PER_SEC );
		std::cout << str_print_buffer <<endl;
#endif
	}while( b_keep_playing );

	const unsigned int closing_seconds = 5;
	std::cout<< "Game Over" << std::endl << "The Game will close in " << closing_seconds << " seconds ..." << std::endl;
	Utility::sleep( closing_seconds * CLOCKS_PER_SEC );

	return 0;
}