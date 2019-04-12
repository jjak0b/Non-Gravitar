#pragma once

#include "DamageableEntity.hpp"

class BunkerA : public DamageableEntity{
    
    public:
        BunkerA( Level *world, Point2D origin, ColoredBitmap *texture, const char classname[], double health );

    
};