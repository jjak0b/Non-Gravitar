#pragma once
#include "Shape.hpp"
#include "Point2D.hpp"

class PlayerShape : public Shape{
    protected:
    float vertx[4];
    float verty[4];
    public:
        PlayerShape(Point2D origin);
        bool ShapeCollision(Shape collision_shape);
};