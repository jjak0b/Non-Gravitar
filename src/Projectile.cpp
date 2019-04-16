#include "Projectile.hpp"
#include "Level.hpp"
#include <stddef.h>

Projectile::Projectile( Level *world, Point2D origin, Vector direction, double damage ) : Entity( world, origin, NULL , "Projectile" ){
    this->origin = origin;
    this->fireOrigin = origin;
    this->direction = direction;
    this->damage = damage;
}

Vector Projectile::GetDirection(){
    return this->direction;
}
double Projectile::GetDamage() {
    return this->damage;
}

double Projectile::GetDamage() {
    return this->damage;
}

bool Projectile::Update( GameEngine *game ) {
    bool shouldUpdateNextFrame = true;
    Point2D current_origin = this->GetOrigin();	
    current_origin.Add( this->direction );
	this->SetOrigin( current_origin );
	return shouldUpdateNextFrame;
}
