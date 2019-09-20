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
        virtual ~Shape();
        
        void addAbsolute( Point2D point );
        void addAbsoluteList( list<Point2D> points );
        void addOffset( Point2D point, Point2D origin);
        list<Point2D> getAbsolutes();
        void deleteAbsolutes();

        bool areIntersecting( Side v1, Side v2 );
        bool ray_Casting(Point2D point, Vector* bounds );
        bool IsShapeColliding( Shape* collision_shape, Vector* bounds );
        void UpdateAbsolutes( Point2D origin, Level *world );
};