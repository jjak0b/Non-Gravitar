#pragma once

#include "Bunker.hpp"
#include "BunkerBShape.hpp"
#include "Projectile.hpp"

class BunkerB : public Bunker{

	public:
		BunkerB( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
		void Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin );
		void Draw( ViewPort *view );
};
