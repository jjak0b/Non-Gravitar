#pragma once

#include "Projectile.hpp"
#include "GameEngine.hpp"
#include "Bunker.hpp"

class BunkerA : public Bunker{
	protected:
        double health = 30;
	
	
	public:
		BunkerA( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
};