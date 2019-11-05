#include "Fuel.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "engine/GameEngine.hpp"
#include <cstring>

Fuel::Fuel( Level *world, Point2D origin) : Entity( world, origin, NULL, "Fuel" ){
	this->enableCollisionLevelDetection = false;
	fuelSize = 0;
	healthSize = 0;
}


void Fuel::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Beam_Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			Player *player = this->world->GetPlayer();
			if( IsDefined( player ) ) {
				player->DoHeal(healthSize);
				player->AddFuel(healthSize);
			}
			this->shouldDeleteOnUpdate = true;
		}
	}
}