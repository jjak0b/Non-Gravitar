#include "Projectile.hpp"
#include "Level.hpp"
#include "GameEngine.hpp"
#include <stddef.h>
#include <ctime>    
#include <cstdlib>  
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>
#include "Entity.hpp"
#include "Point2D.hpp"
#include "SurfaceShape.hpp"

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


	if (IsDefined(this)) {
		if( this->IsOutOfTheWorld() || (game->GetTime() > this->lifetime)) {
		shouldUpdateNextFrame = false;
		this->Delete();
		}
	}

		
	if (shouldUpdateNextFrame == true) {
		std::list<Point2D> surface = this->world->getSurface();
		std::list<Point2D>::iterator surface_it = surface.begin();	
		Point2D start, end;
		while( surface_it != surface.end() ){
			start = *surface_it;
			surface_it++;
			end = *surface_it;
			SurfaceShape surface_shape = SurfaceShape(start, end);
			if (surface_shape.SurfaceCollision(this->GetOrigin()))	{
				shouldUpdateNextFrame = false;	
				this->Delete();
			}
		}																																	
	}	
	return shouldUpdateNextFrame;
}

void Projectile::Draw( ViewPort *view ){
	Entity::Draw( view );
}

void Projectile::Callback_OnCollide(){
	this->Delete();
}



