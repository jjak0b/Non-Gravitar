#pragma once

#include <iostream>
#include "Viewport.hpp"
#include "GameConfig.h"
#include "entities/SolarSystem.hpp"

class GameEngine{
private:
	ViewPort *view;
	INPUT_TYPE input_key;
	double time;
	double deltaTime;
	Level *currentLevel; // livello in esecuzione

	/**
	 * @brief lista di entità contenente i puntatori delle entità considerate da deallocare alla fine del frame
	 * 
	 */
	list<Entity*> garbage_collector;
public:

	GameEngine( unsigned int screen_width = DEFAULT_WINDOW_WIDTH, unsigned int screen_height = DEFAULT_WINDOW_HEIGHT );

	bool update( double deltaTime, INPUT_TYPE key_pressed, unsigned int width, unsigned int height );

	bool frame( double dtime );

	ViewPort* GetViewport();

	void SetCameraWorldOrigin( Point2D origin );

    Point2D GetCameraWorldOrigin();

	INPUT_TYPE GetkeyPressed();

	double GetTime();

	double GetDeltaTime();

	Level *GetCurrentLevel();

	void SetCurrentLevel( Level *level );
	
	void UnloadLevel( Level *last_loaded_level );

	void ClearGarbageCollector();

	void AddGarbage(Entity *entity);
};


/**
 * @brief Verifica se l'entità è significativa nel gioco
 * 
 * @param entity 
 * @return true 
 * @return false 
 */
bool IsDefined( Entity *entity );
