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

		if  ( !strcmp( this->GetClassname(), "Beam_Projectile" ))   {	
		this->texture = new Bitmap( 1, 1, COLOR_BLUE );
		const BITMAP_DATA_TYPE raw_texturer0[] = "\xB1";
		const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0};
		this->texture->Load( rawtexture, NULL, 1, 1);
	}

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

		// Side o = Side(Point2D(this->origin.GetX() - 1, this->origin.GetY()), Point2D(this->origin.GetX() + 1, this->origin.GetY())  );
		// Side t = Side( Point2D(30,40), Point2D(30,20) );
		// if ( this->shape->areIntersecting(t, o, this->world )) {
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
	this->shouldDeleteOnUpdate = true;
}



