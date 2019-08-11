#pragma once

#include "Point2D.hpp"
#include "Vector.hpp"
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
        list<Point2D> getShapePoints();
        list<Side> GetSides();
        
    ///////////////////////////////////////////////////
    bool SideCollision(Shape collision_shape);
    bool onSegment(Point2D p, Point2D q, Point2D r);
    int orientation(Point2D p, Point2D q, Point2D r);
    bool doIntersect(Point2D p1, Point2D q1, Point2D p2, Point2D q2);
    bool PointCollision(Point2D);
    bool PointOnLine(Side side, Point2D point);
    bool SurfaceCollision(Point2D point);
    //////////////////////////////////////////////////    

    /* bool ShapeCollision(Shape collision_shape);
    int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy);
        bool PointCollision(Point2D);
        bool LineOnLine(Side p, Side q);
        */
        

        
    
};