#pragma once

#include "Point2D.hpp"
#include "Side.hpp"

#include <list>
using namespace std;

class Shape{

    protected:
        list<Point2D> points;
    public:

        Shape();
        list<Point2D> getPoints();
        void addPoint( Point2D point );
        void addPointList( list<Point2D> points );
        void deletePoints();
        bool areIntersecting( Side v1, Side v2 );
        bool ray_Casting(Point2D point);
        bool IsShapeColliding( Shape collision_shape );
};