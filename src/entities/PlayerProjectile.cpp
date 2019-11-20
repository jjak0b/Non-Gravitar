#include "PlayerProjectile.hpp" 
#include "engine/GameEngine.hpp"
#include <cstring>


PlayerProjectile::PlayerProjectile( Level *world, Point2D origin, Vector direction, VECTOR_VALUE_TYPE speed, double damage ) : Projectile( world, origin, direction, damage, "Player_Projectile", speed, 4.0 ) {
}

void PlayerProjectile::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	if( strcmp( collide_ent->GetClassname(), "Player" ) ){
		Projectile::Callback_OnCollide( game, collide_ent );
	}
}