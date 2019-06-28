#pragma once

#include "Projectile.hpp"
#include "GameEngine.hpp"
#include "Bunker.hpp"

class BunkerB : public Bunker{

	public:
		BunkerB( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
		void Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin );
};
