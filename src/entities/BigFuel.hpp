#pragma once
#include "Fuel.hpp"

/**
 * @brief Implementazione fuel con quantità di rifornimento grandi
 * 
 */
class BigFuel : public Fuel {
    public:
    BigFuel( Level *world, Point2D origin);
};