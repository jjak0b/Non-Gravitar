#pragma once
#include "Segment.hpp"
#include <list>
using namespace std;

class Level;

#ifdef DEBUG_COLLISION_DRAWING
class GameEngine;
#endif
enum ShapeAddOffsetOption {
	ADD_FRONT = 0,
	ADD_BACK = 1
};

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
        
        void addAbsolute( Point2D point, ShapeAddOffsetOption option = ADD_FRONT );
        void addOffset( Point2D point, Point2D origin, ShapeAddOffsetOption option = ADD_FRONT );
		Point2D PopOffset( ShapeAddOffsetOption option );
        size_t GetOffsetCount();
        list<Point2D> getAbsolutes();
		list<Point2D> getOffsetPoints();
        void deleteAbsolutes();
		void UpdateAbsolutes( Point2D origin );

        bool areIntersecting( Segment a, Segment b, Level *world );
		bool IsPointInShape(Point2D point );
        bool ray_Casting(Point2D point );

		bool IsShapeColliding(
#ifdef DEBUG_COLLISION_DRAWING
								GameEngine* game,
#endif
								Point2D this_origin, Point2D shape_origin, Shape* collision_shape, Vector* bounds );

		bool _areIntersecting( Segment v1, Segment v2 );
};