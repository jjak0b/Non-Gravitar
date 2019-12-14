#pragma once

#include "Bunker.hpp"

/**
 * @brief Implementazione di un Bunker che spara due proiettili in direzioni casuali
 * 
 */
class BunkerA : public Bunker{
	
	public:
		BunkerA( Level *world, Point2D origin);
		bool Update(GameEngine* game);
};
