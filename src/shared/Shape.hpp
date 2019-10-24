#pragma once
#include "Side.hpp"
#include <list>
using namespace std;

class Level;

class Shape{

    protected:
        list<Point2D> absolute_points;
        list<Point2D> offset_points;
		// punto contenente le coordinate minime del bounding box, ovvero le coordinate minime di un rettangolo
		Point2D min_offset = Point2D(0,0);
		// punto contenente le coordinate massime del bounding box, ovvero le coordinate massime di un rettangolo
		Point2D max_offset = Point2D(0,0);
    public:

        Shape();
        virtual ~Shape();
        
        void addAbsolute( Point2D point );
        void addOffset( Point2D point, Point2D origin);
        list<Point2D> getAbsolutes();
		list<Point2D> getOffsetPoints();
        void deleteAbsolutes();
		void UpdateAbsolutes( Point2D origin );

        bool areIntersecting( Side a, Side b, Level *world );
		bool IsPointInShape(Point2D point );
        bool ray_Casting(Point2D point );
        bool IsShapeColliding( Point2D this_origin, Point2D shape_origin, Shape* collision_shape, Vector* bounds );
		bool _areIntersecting( Side v1, Side v2 );
};