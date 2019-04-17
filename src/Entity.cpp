#include "Entity.hpp"
#include "Level.hpp"
#include <cstring>
#include <iostream>

Entity::Entity( Level *world, Point2D origin, ColoredBitmap *texture, const char classname[] ){
	this->str_classname = _strdup( classname );
	this->texture = NULL;
    this->world = world;
	if( this->world != NULL ){
		this->world->AddEntity( this );
	}
    this->SetOrigin( origin );
	this->garbage = false;
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


bool Entity::IsDefined(){
	return !garbage;
}

void Entity::Delete(){
	if( this->texture != NULL ){
		this->texture->Dispose();
		delete this->texture;
	}
	if( this->str_classname != NULL ){
		delete this->str_classname;
	}
}