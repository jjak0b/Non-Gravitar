#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include "GameEngine.hpp"
#include "GameConfig.h"
// dipendenti da SO
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#endif

char getInput(){
            char c = '\0';
        // c = std::cin.get();
        c = _getch();
        if (c == '\033') { // if the first value is esc
            _getch(); // skip the [
            c = _getch();
            switch (c) { // the real value
                case 'A':
                    c = INPUT_ARROW_UP;
                    break;
                case 'B':
                    c = INPUT_ARROW_DOWN;
                    break;
                case 'C':
                    c = INPUT_ARROW_RIGHT;
                    break;
                case 'D':
                    c = INPUT_ARROW_LEFT;
                    break;
            }
        }
        return c;
}

void setCursor( int x, int y ){
	
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = x;
	Position.Y = y;
	SetConsoleCursorPosition(hOut, Position);
}

Point2D GetTerminalSize(){

    #ifdef _WIN32
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

int main(){
    bool b_keep_playing = true;
    double dtime = 0.0;
    char key = '\0';
    clock_t current_time = clock(), last_frame_time = current_time;
    Point2D screen_size = GetTerminalSize();
    system( "CLEAR");
    screen_size.SetX( 120 );
	screen_size.SetY( 30 );
    GameEngine engine = GameEngine( screen_size.GetX(), screen_size.GetY() );
    do{
        setCursor( 0, 0 );
        if( _kbhit() ){
            key = getInput();
        }

        dtime = double( current_time - last_frame_time ) / CLOCKS_PER_SEC;
        if( dtime >= FRAME_TIME ){
			// system("cls");
            last_frame_time = clock();
            engine.update( dtime, key, screen_size.GetX(), screen_size.GetY() );
            b_keep_playing = engine.frame( dtime );
			key = '\0';
#ifdef DEBUG  // DEBUG
			std::cout << "Window: "<<screen_size.GetX() << "x" << screen_size.GetY() << " Duration: " << dtime << "\tFPS: ~" << ceil( 1.0 / dtime ) << std::endl;
#endif
        }
        current_time = clock();
    }while( b_keep_playing );

    return 0;
}