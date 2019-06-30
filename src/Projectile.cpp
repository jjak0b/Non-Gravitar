#include "Projectile.hpp"
#include "Level.hpp"
#include "GameEngine.hpp"
#include <stddef.h>

Projectile::Projectile( Level *world, Point2D origin, Vector direction, double damage, const char classname[] ) : Entity( world, origin, NULL , classname ){
	this->fireOrigin = origin;
	this->direction = direction;
	this->damage = damage;
	this->lifetime = 0;
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

	if (this->lifetime == 0) this->lifetime = game->GetTime() + 4;

	bool shouldUpdateNextFrame = true;

	Point2D current_origin = this->GetOrigin();	
	current_origin.Add( this->direction );
	this->SetOrigin( current_origin );

	if( this->IsOutOfTheWorld() || (game->GetTime() > this->lifetime)){
		shouldUpdateNextFrame = false;
		this->Delete();
	}

	/* for (std::list<Point2D>::iterator it_p = this->world->getSurface().begin(); it_p != this->world->getSurface().end(); it_p++) {
		if (this->GetOrigin().Equals(*it_p)) {
		shouldUpdateNextFrame = false;
		this->Delete();
		}
	}*/
	return shouldUpdateNextFrame;
}

void Projectile::Draw( ViewPort *view ){
	Entity::Draw( view );
}

void Projectile::Callback_OnCollide(){
	this->Delete();
}



