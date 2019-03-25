#include <iostream>
#include "Viewport.hpp"
#include "GameConfig.h"

class GameEngine{
private:
    char input_key;
    double time;
    ViewPort *view;
public:

    GameEngine( unsigned int screen_width = DEFAULT_WINDOW_WIDTH, unsigned int screen_height = DEFAULT_WINDOW_HEIGHT );

    bool update( double time, char key_pressed, unsigned int width, unsigned int height );

    bool frame( double dtime );

    char GetkeyPressed();

    double GetTime();
}