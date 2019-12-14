#include "Entity.hpp"
#include "engine/GameEngine.hpp"
#include "Level.hpp"
#include "engine/GameEngine.hpp"
#include "shared/Shape.hpp"
#include <cstring>
#include <iostream>
#include "shared/Utility.h"

Entity::Entity( Level *_world, Point2D origin, Bitmap *texture, const char classname[], Shape *shape ){
	this->garbage = false;
	this->str_classname = _strdup( classname );
	this->texture = texture;
	this->world = NULL;
	if( IsDefined( _world ) ){
		_world->AddEntity( this );
	}
	this->SetOrigin( origin );
	this->shape = shape;
	this->shouldDeleteOnUpdate = false;
	this->isCollidable = true;
	this->enableCollisionLevelDetection = true;
	
}
Entity::~Entity(){
	if (shape != NULL) {
		delete this->shape;
		this->shape = NULL;
	}

	if( this->str_classname != NULL ){
		delete this->str_classname;
		this->str_classname = NULL;
	}

	if( this->texture != NULL ){
		delete this->texture;
		this->texture = NULL;
	}
}

void Entity::Delete(GameEngine* game ){
	if( !this->garbage ){
		this->SetWorld( NULL );
		this->garbage = true;
		game->AddGarbage(this);
	}
}

Level *Entity::GetWorld(){
	return this->world;
}

void Entity::SetWorld( Level *_world ){
	this->world = _world;
	if( _world != NULL ){
		this->SetOrigin( this->origin ); // Aggiorno le mie coordinate in base al livello in cui si trova
	}
}

Point2D Entity::SetOrigin( const Point2D _origin ){
	if( this->world != NULL ){
		this->origin = this->world->GetNormalizedPoint( _origin );
	}
	else{
		this->origin = _origin;
	}
	return this->origin;
}

Point2D Entity::GetOrigin(){
	return this->origin;
}

char* Entity::GetClassname(){
	return this->str_classname;
}

bool Entity::Update( GameEngine *game ){

	if( this->shouldDeleteOnUpdate ){
		this->Delete( game );
	}
	bool update_result = IsDefined(this);

	return update_result;
}

void Entity::Draw( ViewPort *view ){
	view->Draw( this->texture, this->world, this->GetOrigin() );
}

Shape* Entity::GetShape() {
	return this->shape;
}

void Entity::SetShape( Shape *shape ) {
	this->shape = shape;
}
#ifdef DEBUG_COLLISION_DRAWING
bool Entity::IsColliding( GameEngine* game,  Entity *entity ){
#else
bool Entity::IsColliding( Entity *entity ){
#endif
	if( !IsDefined(entity) || !this->isCollidable || ( IsDefined(entity) && !entity->isCollidable ) ) {
		return false;
	}

	bool imLevel = Utility::CheckEqualsOrSubstring( this->str_classname, "Level" , true );
	bool entIsLevel = Utility::CheckEqualsOrSubstring( entity->str_classname, "Level" , true );
	
	bool isColliding = false;
	Vector* ptr_bounds = NULL;
	Vector bounds;
	if( this->GetWorld() != NULL ) {
		bounds = this->GetWorld()->GetBounds();
		ptr_bounds = &bounds;
		ptr_bounds->Set( 1, 0 );
	}
	if( this->world != NULL && this->shape != NULL && entity->shape != NULL) {
		if( (!imLevel && !entIsLevel)
			|| ( (this->enableCollisionLevelDetection && entIsLevel)
				|| ( entity->enableCollisionLevelDetection && imLevel ) )
			) {
			
			isColliding = this->GetShape()->IsShapeColliding(
#ifdef DEBUG_COLLISION_DRAWING
					game,
#endif
					this->GetOrigin(),
					entity->GetOrigin(),
					entity->GetShape(),
					ptr_bounds);
			
			if (!isColliding) {
				isColliding = entity->GetShape()->IsShapeColliding(
#ifdef DEBUG_COLLISION_DRAWING
						game,
#endif
						entity->GetOrigin(),
						this->GetOrigin(),
						this->GetShape(),
						ptr_bounds);
			}
		}
	}
	return isColliding;
}


bool Entity::IsGarbage(){
	return garbage;
}

bool Entity::IsOutOfTheWorld(){
	if( this->world != NULL ){
		return this->GetOrigin().GetY() <= 0 || this->GetOrigin().GetY() >= this->world->GetMaxHeight();
	}
	return true;
}

void Entity::Callback_OnCollide( GameEngine *game, Entity *collide_ent ){
}

bool Entity::IsCollidable() const {
	return isCollidable;
}
