#include "Projectile.hpp"
#include "engine/GameEngine.hpp"

Projectile::Projectile( Level *world, Point2D origin, Vector direction, double damage, const char classname[], VECTOR_VALUE_TYPE speed, double _lifetime ) : DynamicEntity( world, origin, NULL , classname, speed){
	this->direction = direction;
	this->damage = damage;
	this->lifetime = _lifetime;
	this->deathtime = -1;
	this->SetVelocity( direction.Scale( speed ) );

	this->shape = new Shape();
	this->shape->addOffset(Point2D(0,0), origin);
}

Vector Projectile::GetDirection(){
	return this->direction;
}

double Projectile::GetDamage() {
	return this->damage;
}

bool Projectile::Update( GameEngine *game ) {
	bool update_result = DynamicEntity::Update( game );

	if (this->deathtime < 0) { // inizializza il momento in cui deve essere eliminato
		this->deathtime = game->GetTime() + this->lifetime;
	}

	if( update_result ){
		// eliminazione per tempo di vita o posizione esterna al pianeta
		if( game->GetTime() > this->deathtime || this->IsOutOfTheWorld()  ) {
			update_result = false;
		}
	}

	return update_result;
}

void Projectile::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	this->shouldDeleteOnUpdate = true;
}



