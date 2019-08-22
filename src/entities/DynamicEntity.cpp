#include "DynamicEntity.hpp"
#include "engine/GameEngine.hpp"

DynamicEntity::DynamicEntity(Level *world, Point2D origin, Bitmap *texture, const char classname[], VECTOR_VALUE_TYPE speed_max ) : Entity(world, origin, texture, classname){
	this->velocity = new Vector();
	this->previous_velocity = new Vector();
	this->speed_max = speed_max;
}

DynamicEntity::~DynamicEntity(){
	delete this->velocity;
	this->velocity = NULL;
	delete this->previous_velocity;
	this->previous_velocity = NULL;
}

VECTOR_VALUE_TYPE DynamicEntity::GetSpeed(){
	return this->velocity->Lenght();
}

VECTOR_VALUE_TYPE DynamicEntity::GetMaxSpeed(){
	return this->speed_max;
}

void DynamicEntity::SetVelocity(Vector _velocity) {
	*this->previous_velocity = *this->velocity;
	// rimodulo la velocità
	if ( !_velocity.Lenght() > speed_max ){
		_velocity.Normalize();
		_velocity.Scale( this->speed_max );
	}
	*this->velocity = _velocity;
}

Vector DynamicEntity::GetVelocity() {
	return *this->velocity;
}

bool DynamicEntity::Update( GameEngine *game ){
	bool update_result = Entity::Update( game );

	if( update_result ){
		double deltaTime = game->GetDeltaTime();
		Point2D updated_origin = this->GetOrigin();
		updated_origin.Add( GetVelocity().Scale( deltaTime )); // pos_f = pos_i + v*t
		this->SetOrigin( updated_origin );
	}

	return update_result;
}


