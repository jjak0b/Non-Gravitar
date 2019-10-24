#pragma once
#include "Bunker.hpp"

class BunkerC : public Bunker{

	public:
		BunkerC( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
};

