#pragma once

#include "Fuel.hpp"
#include "Level.hpp"
#include "Point2D.hpp"

class SmallFuel : public Fuel {
    public:
    SmallFuel( Level *world, Point2D origin);
    bool Update(GameEngine *game);
};