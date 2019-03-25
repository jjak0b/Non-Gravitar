#include <time.h>
#include <conio.h>
#include "GameEngine.hpp"
#include "GameConfig.h"
// dipendenti da SO
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#endif

char getInput(){
            char c = '\0';
        c = std::cin.get();
        if (c == '\033') { // if the first value is esc
            std::cin.get(); // getchar(); // skip the [
            c = std::cin.get();// c = getchar();
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

Point2D GetTerminalSize(){
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
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

    bool b_endGame = false;
    double dtime = 0.0;
    char key = '\0';
    clock_t current_time = clock(), last_frame_time = current_time;
    Point2D screen_size = GetTerminalSize();
    GameEngine engine = GameEngine( screen_size.x, screen_size.y );
    do{
        if( kbhit() ){
            key = getInput();
        }
        else{
            key = '\0';
        }
        dtime = double(last_frame_time - current_time) / CLOCKS_PER_SEC;
        if( dtime >= FRAME_TIME ){
            last_frame_time = clock();
            engine.update( dtime, key, 0, 0 );
            b_endGame = engine.frame( dtime );
        }
        current_time = clock();
    }while( !b_endGame );

    return 0;
}