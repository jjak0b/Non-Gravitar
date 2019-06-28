#pragma once

#include "Projectile.hpp"
#include "GameEngine.hpp"
#include "Bunker.hpp"

class BunkerB : public Bunker{
	protected:
        double health = 30;
	
	
	public:
		BunkerB( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
};