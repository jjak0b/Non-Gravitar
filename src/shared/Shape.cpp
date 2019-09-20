#include "Shape.hpp"
#include "Point2D.hpp"
#include "Vector.hpp"
#include "Side.hpp"
#include <cmath>
#include "entities/Level.hpp"


Shape::Shape() {
};

Shape::~Shape() {
  this->absolute_points.clear();
  this->offset_points.clear();
};


void Shape::addAbsolute( Point2D point ) {
  this->absolute_points.push_front(point);
}

void Shape::addAbsoluteList( list<Point2D> point_list ) {
  
  std::list<Point2D>::iterator it = point_list.begin();
  for (it; it !=  point_list.end(); it++) {
      addAbsolute( (*it) );
  }
}

void Shape::addOffset( Point2D point, Point2D origin ) {
  this->offset_points.push_front(point);
  origin.Add(point);
  addAbsolute(origin);
}

list<Point2D> Shape::getAbsolutes() {
  return this->absolute_points;
}

void Shape::deleteAbsolutes() {
  this->absolute_points.clear();
}

void Shape::UpdateAbsolutes( Point2D origin, Level *world ) {

  
  Point2D point;
  list<Point2D>::iterator it_offset, it_absolute;
  it_offset = this->offset_points.begin();
  it_absolute = this->absolute_points.begin();
  
  for (; it_offset != this->offset_points.end(); it_offset++, it_absolute++ ) {
    
    point = origin;
    point.Add(*it_offset);
    point = world->GetNormalizedPoint(point);
    (*it_absolute) = point;
  }
}

// Intersezioni
bool Shape::IsShapeColliding( Shape* collision_shape, Vector* bounds ) {
  
  list<Point2D> collision_points = collision_shape->getAbsolutes();
  std::list<Point2D>::iterator it = collision_points.begin();
  bool is_Colliding = false;

  while( !is_Colliding && it != collision_points.end() ){
    if ( this->ray_Casting(*it, bounds ) ) is_Colliding = true;
    it++;
  }
  if (is_Colliding) return true;
  else return false;
}


bool Shape::ray_Casting(Point2D point, Vector* bounds ) {

  int intersections = 0;
  float e = 1.0;

  // Imposta i valori minimi e massimi del poligono
  float Xmin = this->absolute_points.front().GetX();
  float Xmax = this->absolute_points.front().GetX();
  float Ymin = this->absolute_points.front().GetY();
  float Ymax = this->absolute_points.front().GetY(); 
        
  std::list<Point2D>::iterator it = this->absolute_points.begin();
  it++;
  for (it; it !=  this->absolute_points.end(); it++) {

    if ( (*it).GetX() < Xmin ) Xmin = (*it).GetX();
    if ( (*it).GetX() > Xmax ) Xmax = (*it).GetX();
    if ( (*it).GetY() < Ymin ) Ymin = (*it).GetY();
    if ( (*it).GetY() > Ymax ) Ymax = (*it).GetY();

  }

  Point2D point_min = Point2D( Xmin, Ymin );
  Point2D point_max = Point2D( Xmax, Ymax );

  VECTOR_VALUE_TYPE
  	distance_X_point_to_X_min,
  	distance_X_point_to_X_max,
	distance_Y_point_to_Y_min,
	distance_Y_point_to_Y_max;

	GetOffSet(&distance_X_point_to_X_min, point_min, point, BOUND_INDEX_WIDTH, bounds ); // point.GetX() < Xmin -> point.GetX() - Xmin < 0
	GetOffSet(&distance_X_point_to_X_max, point_max, point, BOUND_INDEX_WIDTH, bounds ); // point.GetX() > Xmax -> point.GetX() - Xmax > 0
	GetOffSet(&distance_Y_point_to_Y_min, point_min, point, BOUND_INDEX_HEIGHT, bounds ); // point.GetY() < Ymin -> point.GetY() - Ymin < 0
	GetOffSet(&distance_Y_point_to_Y_max, point_max, point, BOUND_INDEX_HEIGHT, bounds ); // point.GetY() > Ymax -> point.GetY() - Ymax > 0
	if (distance_X_point_to_X_min < 0 || distance_X_point_to_X_max > 0 || distance_Y_point_to_Y_min < 0 || distance_Y_point_to_Y_max > 0) {
		return false;
	}

  // conta le intersezioni del ray con i lati del poligono
  Point2D ray_A = Point2D( ( Xmin - e/point.GetY() ) , point.GetY());
  Side ray = Side(ray_A, point);
        

  it =this->absolute_points.begin();
      
  Point2D start, end;
  while( it != this->absolute_points.end() ){
    start = *it;
    it++;
    end = *it;
    Side side = Side( start, end );
    if (areIntersecting ( side, ray ) ) intersections ++;   }

    // Se le intersezioni sono dispari il punto è all'interno del poligono
    if ((intersections & 1) == 1) {
    // Inside of polygon
      return true;
    } else {
      // Outside of polygon
      return false;
    }
  }   

bool Shape::areIntersecting( Side v1, Side v2) {
    
    float v1x1 = v1.getA().GetX();
    float v1y1 = v1.getA().GetY();
    float v1x2 = v1.getB().GetX();
    float v1y2 = v1.getB().GetY();

    float v2x1 = v2.getA().GetX();
    float v2y1 = v2.getA().GetY();
    float v2x2 = v2.getB().GetX();
    float v2y2 = v2.getB().GetY();

    float d1, d2;
    float a1, a2, b1, b2, c1, c2;

    // Convert vector 1 to a line (line 1) of infinite length.
    // We want the line in linear equation standard form: A*x + B*y + C = 0
    // See: http://en.wikipedia.org/wiki/Linear_equation
    a1 = v1y2 - v1y1;
    b1 = v1x1 - v1x2;
    c1 = (v1x2 * v1y1) - (v1x1 * v1y2);

    // Every point (x,y), that solves the equation above, is on the line,
    // every point that does not solve it, is not. The equation will have a
    // positive result if it is on one side of the line and a negative one 
    // if is on the other side of it. We insert (x1,y1) and (x2,y2) of vector
    // 2 into the equation above.
    d1 = (a1 * v2x1) + (b1 * v2y1) + c1;
    d2 = (a1 * v2x2) + (b1 * v2y2) + c1;

    // If d1 and d2 both have the same sign, they are both on the same side
    // of our line 1 and in that case no intersection is possible. Careful, 
    // 0 is a special case, that's why we don't test ">=" and "<=", 
    // but "<" and ">".
    if (d1 > 0 && d2 > 0) return false;
    if (d1 < 0 && d2 < 0) return false;

     // The fact that vector 2 intersected the infinite line 1 above doesn't 
    // mean it also intersects the vector 1. Vector 1 is only a subset of that
    // infinite line 1, so it may have intersected that line before the vector
    // started or after it ended. To know for sure, we have to repeat the
    // the same test the other way round. We start by calculating the 
    // infinite line 2 in linear equation standard form.
    a2 = v2y2 - v2y1;
    b2 = v2x1 - v2x2;
    c2 = (v2x2 * v2y1) - (v2x1 * v2y2);

    // Calculate d1 and d2 again, this time using points of vector 1.
    d1 = (a2 * v1x1) + (b2 * v1y1) + c2;
    d2 = (a2 * v1x2) + (b2 * v1y2) + c2;

    // Again, if both have the same sign (and neither one is 0),
    // no intersection is possible.
    if (d1 > 0 && d2 > 0) return false;
    if (d1 < 0 && d2 < 0) return false;

    // If we get here, only two possibilities are left. Either the two
    // vectors intersect in exactly one point or they are collinear, which
    // means they intersect in any number of points from zero to infinite.
    // If they are not collinear, they must intersect in exactly one point.
    return true;
}