#include "Entity.hpp"
#include "Level.hpp"
#include <cstring>
#include <iostream>

Entity::Entity( Level *world, Point2D origin, ColoredBitmap *texture, const char classname[] ){
	this->str_classname = _strdup( classname );
	this->texture = NULL;
    this->world = world;
	
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

void Entity::Draw( ViewPort *view ){
	view->Draw( this->texture, this->world, this->GetOrigin() );
}

bool Entity::IsColliding( Entity *entity, Point2D *collisionOrigin ){
	bool isColliding = false;
	Point2D collidingPoint;
	// TODO
	if( collisionOrigin != NULL ){
		*collisionOrigin = collidingPoint;
	}
	return isColliding;
}