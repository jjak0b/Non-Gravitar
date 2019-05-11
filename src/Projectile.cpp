#include "Projectile.hpp"
#include "Level.hpp"
#include <stddef.h>

Projectile::Projectile( Level *world, Point2D origin, Vector direction, double damage ) : Entity( world, origin, NULL , "Projectile" ){
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

Point2D Projectile::GetFireOrigin(){
    return this->fireOrigin;
}

bool Projectile::Update( GameEngine *game ) {
    bool shouldUpdateNextFrame = true;

    Point2D current_origin = this->GetOrigin();	
    current_origin.Add( this->direction );
    this->SetOrigin( current_origin );

    if( this->IsOutOfTheWorld() ){
        shouldUpdateNextFrame = false;
        this->garbage = true;
    }
	return shouldUpdateNextFrame;
}

void Projectile::Draw( ViewPort *view ){
    Entity::Draw( view );
}

void Projectile::Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin ){
    this->garbage = true;
}