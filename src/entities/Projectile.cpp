#include "Projectile.hpp"
#include "Level.hpp"
#include "engine/GameEngine.hpp"
#include "Damageable.hpp"
#include "shared/Shape.hpp"
#include <cstring>
#include <iostream>
#include "Player.hpp"
#include "Beam.hpp"

Projectile::Projectile( Level *world, Point2D origin, Vector direction, double damage, const char classname[], VECTOR_VALUE_TYPE speed, double _lifetime ) : DynamicEntity( world, origin, NULL , classname, speed){
	this->fireOrigin = origin;
	this->direction = direction;
	this->damage = damage;
	this->lifetime = _lifetime;
	this->deathtime = -1;
	this->SetVelocity( direction.Scale( speed ) );

	this->shape = new Shape();
	this->shape->addOffset(Point2D(0,0), origin);

	//if  ( !strcmp( this->GetClassname(), "Beam_Projectile" )) this->beam = new Beam(world, origin);
}

Vector Projectile::GetDirection(){
	return this->direction;
}

double Projectile::GetDamage() {
	return this->damage;
}

Point2D Projectile::GetFireOrigin(){
	return this->fireOrigin;
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
		//if (update_result && this->beam != NULL) this->beam->addNext(origin);

	}
	
	if( !update_result ){
			//if (this->beam != NULL) this->beam->Delete(game);
            this->Delete( game );
		}

	return update_result;
}

void Projectile::Draw( ViewPort *view ){
	DynamicEntity::Draw( view );
}

void Projectile::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	this->shouldDeleteOnUpdate = true;
}



