#include "DamageableEntity.hpp"

DamageableEntity::DamageableEntity( Level *world, Point2D origin, ColoredBitmap *texture, char *classname, double healthmax) : Entity( world, origin, texture, classname ){
    this->SetMaxHealth( healthmax );
    this->SetHealth( healthmax );
}