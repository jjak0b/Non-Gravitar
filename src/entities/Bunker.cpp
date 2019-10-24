#include "Bunker.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "engine/GameEngine.hpp"
#include <cstring>

Bunker::Bunker( Level *world, Point2D origin, double health, const char classname[] ) : Entity( world, origin, NULL, classname ), Damageable( health ) {
}

bool Bunker::Update(GameEngine* game) {
	bool update_result = this->Entity::Update( game );

	if (health <= 0){
		update_result = false;
		Player* player = this->GetWorld()->GetPlayer();
		if( IsDefined( player ) )
			player->AddScore( PLAYER_SCORE_BUNKER_DESTROYED );
		this->Delete( game );
	}

    return update_result;
}

Projectile *Bunker::Shoot(Point2D projectile_origin, Vector direction ){
	projectile_origin.Add( direction ); 
	Projectile *p = new Projectile( this->world, projectile_origin, direction, 5, "Projectile" );
	return p;
}

void Bunker::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Player_Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			this->DoDamage(proj->GetDamage());
		}
		else if ( !strcmp( collide_ent->GetClassname(), "Player" ) ) { 
			this->DoDamage( this->GetHealth());
		}
	}
}