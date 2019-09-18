#pragma once

#include "Point2D.hpp"
#include "Side.hpp"

#include <list>
using namespace std;

class Level;

class Shape{

    protected:
        list<Point2D> absolute_points;
        list<Point2D> offset_points;

    public:

        Shape();

        
        void addAbsolute( Point2D point );
        void addAbsoluteList( list<Point2D> points );
        void addOffset( Point2D point );
        list<Point2D> getAbsolutes();

        bool areIntersecting( Side v1, Side v2 );
        bool ray_Casting(Point2D point);
        bool IsShapeColliding( Shape collision_shape );
        void UpdateAbsolutes( Point2D origin, Level *world );
};