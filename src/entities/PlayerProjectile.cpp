#include "PlayerProjectile.hpp" 
#include "engine/GameEngine.hpp"
#include <cstring>


PlayerProjectile::PlayerProjectile( Level *world, Point2D origin, Vector direction, VECTOR_VALUE_TYPE speed) : Projectile( world, origin, direction, 50, "Player_Projectile", speed, 4.0 ) {
}

void PlayerProjectile::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	if( strcmp( collide_ent->GetClassname(), "Player" ) ){
			this->shouldDeleteOnUpdate = true;
		}
}