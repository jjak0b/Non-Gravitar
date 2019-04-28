#include "Entity.hpp"
#include "GameEngine.hpp"
#include "Level.hpp"
#include <cstring>
#include <iostream>

Entity::Entity( Level *world, Point2D origin, ColoredBitmap *texture, const char classname[] ){
	this->garbage = false;
	this->str_classname = _strdup( classname );
	this->texture = NULL;
    this->world = world;
	if( this->world != NULL && strcmp( this->str_classname, "Player" ) ){
		this->world->AddEntity( this );
	}
    this->SetOrigin( origin );
}

Point2D Entity::SetOrigin( Point2D _origin ){
	if( this->world != NULL ){
		this->origin = this->world->GetNormalizedPoint( _origin );
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
	if( IsDefined( this ) ){
		return true;
	}
	return false;
}

void Entity::Draw( ViewPort *view ){
	view->Draw( this->texture, this->world, this->GetOrigin() );
}

bool Entity::IsColliding( Entity *entity, Point2D *collisionOrigin ){
	bool isColliding = false;
	Point2D collidingPoint;
	if( !strcmp(entity->GetClassname(), "Level" ) ){
		this->world->IsColliding( entity, collisionOrigin );
	}
	else{
		// TODO
	}

	if( collisionOrigin != NULL ){
		*collisionOrigin = collidingPoint;
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

void Entity::Delete(){
	if( this->texture != NULL ){
		this->texture->Dispose();
		delete this->texture;
	}
	if( this->str_classname != NULL ){
		delete this->str_classname;
	}
	this->garbage = true;
}
