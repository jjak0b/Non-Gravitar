#pragma once

#include "Projectile.hpp"
#include "Level.hpp"
#include <stddef.h>

Projectile::Projectile( Level *world, Point2D fireOrigin, Point2D targetOrigin, double damage, Entity *owner ) : Entity( world, fireOrigin, NULL , "Projectile" ){
    this->owner = owner;
    this->fireOrigin = fireOrigin;
    this->targetOrigin = targetOrigin;
    this->damage = damage;
}
