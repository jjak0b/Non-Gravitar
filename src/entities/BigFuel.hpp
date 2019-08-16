#pragma once

#include "Fuel.hpp"
#include "Level.hpp"
#include "shared/Point2D.hpp"

class BigFuel : public Fuel {
    public:
    BigFuel( Level *world, Point2D origin);
    bool Update(GameEngine *game);
};