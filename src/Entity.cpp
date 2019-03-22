#include "Entity.hpp"
#include <cstring>

Entity::Entity( Level *world, Point2D origin, ColoredBitmap *texture, char classname[] ){
    strcpy( this->str_classname, classname );
    this->texture = texture;
    this->world = world;
    this->SetOrigin( origin );
}