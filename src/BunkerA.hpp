#pragma once

#include "Projectile.hpp"
#include "GameEngine.hpp"

class BunkerA : public Bunker{
	
	
	public:
		BunkerA( Level *world, Point2D origin);
	    bool Update(GameEngine* game);
		void Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin );
		void Draw( ViewPort *view );
		
};