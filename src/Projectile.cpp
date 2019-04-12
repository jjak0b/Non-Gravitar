#include "Projectile.hpp"
#include "Level.hpp"
#include <stddef.h>



Projectile::Projectile( Level *world, Point2D origin, Point2D targetOrigin, double damage, char lastInput) : Entity( world, fireOrigin, NULL , "Projectile" ){
    
    this->origin = origin;
    this->targetOrigin = targetOrigin;
    this->damage = damage;
    this->lastInput = lastInput;
    
}



Point2D Projectile::GetTargetOrigin() {
    return this->targetOrigin;
};

double Projectile::GetDamage() {
    return this->damage;
};


void Projectile::GetTargetOrigin(Point2D target) {
    this->targetOrigin = target;
};

void Projectile::GetDamage(double damage) {
    this->damage = damage;
};


bool Projectile::Update() {
    

    Point2D current_origin = this->GetOrigin();	

    

    if (this->lastInput == 's')
        current_origin.y -= 1;
    if (this->lastInput == 'w')
        current_origin.y += 1;
    if (this->lastInput == 'a')
        current_origin.x -= 1;
    if (this->lastInput == 'd')
        current_origin.x += 1;
    


	this->SetOrigin( current_origin );

	return false;
};
