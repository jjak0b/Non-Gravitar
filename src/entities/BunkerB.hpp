#pragma once
#include "Bunker.hpp"

/**
 * @brief Implementazione di un Bunker che spara true proiettili in direzioni diverse ma costanti
 * 
 */
class BunkerB : public Bunker{

	public:
		BunkerB( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
};
