#pragma once

#include "Bunker.hpp"
#include "Projectile.hpp"

class BunkerC : public Bunker{

	public:
		BunkerC( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
		void Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin );
		void Draw( ViewPort *view );
};

