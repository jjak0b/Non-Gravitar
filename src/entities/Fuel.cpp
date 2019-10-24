#include "Fuel.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "engine/GameEngine.hpp"
#include <cstring>

Fuel::Fuel( Level *world, Point2D origin) : Entity( world, origin, NULL, "Fuel" ){
}


void Fuel::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Beam_Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			this->world->GetPlayer()->DoHeal(size);
			this->shouldDeleteOnUpdate = true;
		}
	}
}