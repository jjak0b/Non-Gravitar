#pragma once

#include "Point2D.hpp"
#include "Side.hpp"

#include <list>
using namespace std;

class Shape{

    protected:
        Point2D origin;
        list<Point2D> points;
        list<Side> sides;

    public:

        Shape( Point2D origin);
        list<Point2D> getPoints();
        void addPoint( Point2D point );
        void addPointList( list<Point2D> points );
        bool areIntersecting( Side v1, Side v2 );
        bool ray_Casting(Point2D point);


    // list<Side> GetSides();
    //     void addSide( Side side );
    // ///////////////////////////////////////////////////
    // bool SideCollision(Shape collision_shape);
    // bool onSegment(Point2D p, Point2D q, Point2D r);
    // int orientation(Point2D p, Point2D q, Point2D r);
    // bool doIntersect(Point2D p1, Point2D q1, Point2D p2, Point2D q2);
    // bool PointCollision(Point2D);
    // bool PointOnLine(Side side, Point2D point);
    // bool SurfaceCollision(Point2D point);
    // //////////////////////////////////////////////////    
    // bool pointOnSegment( Point2D start, Point2D end, Point2D point);
};