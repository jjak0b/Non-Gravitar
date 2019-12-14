#pragma once
#include "Fuel.hpp"

/**
 * @brief Implementazione fuel con quantità di rifornimento ridotte
 * 
 */
class SmallFuel : public Fuel {
    public:
    SmallFuel( Level *world, Point2D origin);
};