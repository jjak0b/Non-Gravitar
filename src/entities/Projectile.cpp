#include "Projectile.hpp"
#include "Level.hpp"
#include "engine/GameEngine.hpp"
#include "Damageable.hpp"
#include "SurfaceShape.hpp"

Projectile::Projectile( Level *world, Point2D origin, Vector direction, double damage, const char classname[], VECTOR_VALUE_TYPE speed ) : DynamicEntity( world, origin, NULL , classname, speed){
	this->fireOrigin = origin;
	this->direction = direction;
	this->damage = damage;
	this->lifetime = 0;
	this->SetVelocity( direction.Scale( speed ) );
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

	if (this->lifetime == 0) {
		this->lifetime = game->GetTime() + 4;
	}

	if( update_result ){

		bool isCollisionDetected = false;

		std::list<Point2D> surface = this->world->getSurface();
		std::list<Point2D>::iterator surface_it = surface.begin();
		Point2D start, end;
		while( !isCollisionDetected && surface_it != surface.end() ){
			start = *surface_it;
			surface_it++;
			end = *surface_it;
			SurfaceShape surface_shape = SurfaceShape(start, end);
			if (surface_shape.SurfaceCollision(this->GetOrigin()))	{
				isCollisionDetected = true;
			}
		}

		if( isCollisionDetected ){
			this->Callback_OnCollide();
			update_result = false;
		}
		else if(  this->IsOutOfTheWorld() || (game->GetTime() > this->lifetime)) {
			this->Delete();
			update_result = false;
		}
	}

	return update_result;
}

void Projectile::Draw( ViewPort *view ){
	DynamicEntity::Draw( view );
}

void Projectile::Callback_OnCollide(){
	this->Delete();
}
void Projectile::Callback_OnCollide( Damageable* entity ){
	entity->DoDamage( this->GetDamage() );
	this->Callback_OnCollide();
}



