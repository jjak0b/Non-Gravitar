#pragma once

#include "Bunker.hpp"
#include "Projectile.hpp"

class BunkerC : public Bunker{

	public:
		BunkerC( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
		void Draw( ViewPort *view );
};

