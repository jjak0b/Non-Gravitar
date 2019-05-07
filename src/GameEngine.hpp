#pragma once

#include <iostream>
#include "Viewport.hpp"
#include "GameConfig.h"
#include "SolarSystem.hpp"

class GameEngine{
private:
    INPUT_TYPE input_key;
    double time;
    Level *currentLevel; // livello in esecuzione
	SolarSystem *currentSolarSystem; // Sistema solare di riferimento attivo
    ViewPort *view;
public:

    GameEngine( unsigned int screen_width = DEFAULT_WINDOW_WIDTH, unsigned int screen_height = DEFAULT_WINDOW_HEIGHT );

    bool update( double time, INPUT_TYPE key_pressed, unsigned int width, unsigned int height );

    bool frame( double dtime );

    INPUT_TYPE GetkeyPressed();

    double GetTime();

    Level *GetCurrentLevel();

    void SetCurrentLevel( Level *level );

    SolarSystem *GetCurrentSolarSystem();

    void SetCurrentSolarSystem( SolarSystem *solarsystem );
    
};


/**
 * @brief Verifica se l'entità è significativa nel gioco
 * 
 * @param entity 
 * @return true 
 * @return false 
 */
bool IsDefined( Entity *entity );