#include "Projectile.hpp"
#include "Level.hpp"
#include "engine/GameEngine.hpp"
#include "Damageable.hpp"
#include "shared/Shape.hpp"
#include <cstring>
#include <iostream>
#include "Player.hpp"

Projectile::Projectile( Level *world, Point2D origin, Vector direction, double damage, const char classname[], VECTOR_VALUE_TYPE speed, double _lifetime ) : DynamicEntity( world, origin, NULL , classname, speed){
	this->fireOrigin = origin;
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

Point2D Projectile::GetFireOrigin(){
	return this->fireOrigin;
}

bool Projectile::Update( GameEngine *game ) {
	bool update_result = DynamicEntity::Update( game );

	if (this->deathtime < 0) { // inizializza il momento in cui deve essere eliminato
		this->deathtime = game->GetTime() + this->lifetime;
	}


	if( update_result ){

		bool isCollisionDetected = false;

		// // controllo collisione surface
		// std::list<Point2D> surface = this->world->GetShape()->getAbsolutes();
		// Shape surface_shape = Shape();
		// surface_shape.addAbsoluteList(surface);
		
		// if (surface_shape.ray_Casting(this->GetOrigin()))	{
		// 	isCollisionDetected = true;	
		// }

		// eliminazione per collisione o posizione esterna al pianeta
		if( isCollisionDetected || this->IsOutOfTheWorld() ){
			this->Delete();
			update_result = false;
		}

		// eliminazione per tempo di vita
		else if( game->GetTime() > this->deathtime ) {
			this->Delete();
			update_result = false;
		}
	}

	return update_result;
}

void Projectile::Draw( ViewPort *view ){
	DynamicEntity::Draw( view );
}

void Projectile::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	
	this->Delete();
	
}



