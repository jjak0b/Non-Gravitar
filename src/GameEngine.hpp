#pragma once

#include <iostream>
#include "Viewport.hpp"
#include "GameConfig.h"

class GameEngine{
private:
    char input_key;
    double time;
    Level *level;
    ViewPort *view;
public:

    GameEngine( unsigned int screen_width = DEFAULT_WINDOW_WIDTH, unsigned int screen_height = DEFAULT_WINDOW_HEIGHT );

    bool update( double time, INPUT_TYPE key_pressed, unsigned int width, unsigned int height );

    bool frame( double dtime );

    INPUT_TYPE GetkeyPressed();

    double GetTime();
};