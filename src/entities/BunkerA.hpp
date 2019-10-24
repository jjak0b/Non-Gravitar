#pragma once

#include "Bunker.hpp"

class BunkerA : public Bunker{
	
	public:
		BunkerA( Level *world, Point2D origin);
		bool Update(GameEngine* game);
};
