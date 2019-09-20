#include "Entity.hpp"
#include "engine/GameEngine.hpp"
#include "Level.hpp"
#include <cstring>
#include <iostream>
#include "engine/GameEngine.hpp"
#include "shared/Shape.hpp"


Entity::Entity( Level *_world, Point2D origin, Bitmap *texture, const char classname[], Shape *shape ){
	this->garbage = false;
	this->str_classname = _strdup( classname );
	this->texture = NULL;
	if( IsDefined( _world ) ){
		_world->AddEntity( this );
	}
	this->SetOrigin( origin );
}
Entity::~Entity(){
	if (shape != NULL) {
		delete this->shape;
		this->shape = NULL;
	}
	this->Entity::Delete();

	if( this->str_classname != NULL ){
		delete this->str_classname;
		this->str_classname = NULL;
	}

	if( this->texture != NULL ){
		delete this->texture;
		this->texture = NULL;
	}
}

void Entity::Delete(){
	if( !this->IsGarbage() ){
		this->SetWorld( NULL );
		this->garbage = true;
		//game->AddGarbage(this);
		// TODO: Aggiungere entità al garbage collector
		
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

Point2D Entity::SetOrigin( Point2D _origin ){
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

	if ( IsDefined(this) && this->shape != NULL  ) this->shape->UpdateAbsolutes( this->GetOrigin(), this->GetWorld() );
	return IsDefined(this);
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

bool Entity::IsColliding( Entity *entity ){
	if ( this->shape == NULL || entity->shape == NULL ) return false;
	else return (*this->GetShape()).IsShapeColliding( (*(*entity).GetShape()) );
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
	




