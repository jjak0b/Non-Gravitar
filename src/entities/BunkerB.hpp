#pragma once
#include "Bunker.hpp"

class BunkerB : public Bunker{

	public:
		BunkerB( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
};
