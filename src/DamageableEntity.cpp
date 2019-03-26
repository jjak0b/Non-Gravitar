#include "DamageableEntity.hpp"
#include "Entity.hpp"

DamageableEntity::DamageableEntity( Level *world, Point2D origin, ColoredBitmap *texture, const char classname[], double healthmax) : Entity( world, origin, texture, classname ){
    this->SetMaxHealth( healthmax );
    this->SetHealth( healthmax );
}