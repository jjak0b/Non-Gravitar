#include "Entity.hpp"
#include "Level.hpp"
#include <cstring>
#include <iostream>

Entity::Entity( Level *world, Point2D origin, ColoredBitmap *texture, const char classname[] ){
    strcpy( this->str_classname, classname );
    if( texture != NULL ){
        this->texture = *texture;
    }
    else{
        this->texture = ColoredBitmap( 1, 1, 0 );
    }
    this->world = world;
    this->SetOrigin( origin );
}

Point2D Entity::SetOrigin( Point2D origin ){
    origin.x = origin.x % this->world->GetMaxWidth();
    origin.y = origin.y % this->world->GetMaxHeight();
}

Point2D Entity::GetOrigin(){
    return this->origin;
}

void Entity::Draw( ViewPort *view ){
    if( this->texture.GetColumns() == 1 && this->texture.GetRows() == 1 ){
        view->SetPixel( this->GetOrigin() );
    }
    else{
        // TODO
    }
}