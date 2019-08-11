#pragma once

#include "Fuel.hpp"
#include "Level.hpp"
#include "Point2D.hpp"

class BigFuel : public Fuel {
    public:
    BigFuel( Level *world, Point2D origin);
    bool Update(GameEngine *game);
};