#pragma once

#include "Bunker.hpp"
#include "Projectile.hpp"

class BunkerB : public Bunker{

	public:
		BunkerB( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
		void Draw( ViewPort *view );
};
