#pragma once
#include "Bunker.hpp"

/**
 * @brief Implementazione di un Bunker che spara 2 proiettili in direzione verticale, uno a breve tempo dall'altro
 * quasi consecutivi ma in frame diversi
 * 
 */
class BunkerC : public Bunker{

	public:
		BunkerC( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
};

