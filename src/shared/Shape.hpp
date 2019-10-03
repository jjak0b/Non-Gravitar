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
		list<Point2D> getOffsetPoints();
        void deleteAbsolutes();

        bool areIntersecting( Side a, Side b, Level *world );
        bool ray_Casting(Point2D point, Level* world );
        bool IsShapeColliding( Point2D o1, Point2D o2, Shape* collision_shape, Level *world );
        void UpdateAbsolutes( Point2D origin, Level *world );
		bool _areIntersecting( Side v1, Side v2, Level *world );
};