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

 if ( world != NULL )  {
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
}

// Intersezioni
bool Shape::IsShapeColliding( Shape* collision_shape, Level *world ) {
  
  list<Point2D> collision_points = collision_shape->getAbsolutes();
  std::list<Point2D>::iterator it = collision_points.begin();
  bool is_Colliding = false;

  while( !is_Colliding && it != collision_points.end() ){
    if ( this->ray_Casting(*it, world ) ) is_Colliding = true;
    it++;
  }
  if (is_Colliding) return true;
  else return false;
}


bool Shape::ray_Casting(Point2D point, Level *world ) {

  int intersections = 0;
  float e = 1.0;
  Vector* ptr_bounds = NULL;
	Vector bounds;
	bounds = world->GetBounds();
	ptr_bounds = &bounds;

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

	GetOffSet(&distance_X_point_to_X_min, point_min, point, BOUND_INDEX_WIDTH, ptr_bounds ); // point.GetX() < Xmin -> point.GetX() - Xmin < 0
	GetOffSet(&distance_X_point_to_X_max, point_max, point, BOUND_INDEX_WIDTH, ptr_bounds ); // point.GetX() > Xmax -> point.GetX() - Xmax > 0
	GetOffSet(&distance_Y_point_to_Y_min, point_min, point, BOUND_INDEX_HEIGHT, ptr_bounds ); // point.GetY() < Ymin -> point.GetY() - Ymin < 0
	GetOffSet(&distance_Y_point_to_Y_max, point_max, point, BOUND_INDEX_HEIGHT, ptr_bounds ); // point.GetY() > Ymax -> point.GetY() - Ymax > 0
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
    if (areIntersecting ( side, ray, world) ) intersections ++;   }

    // Se le intersezioni sono dispari il punto è all'interno del poligono
    if ((intersections & 1) == 1) {
    // Inside of polygon
      return true;
    } else {
      // Outside of polygon
      return false;
    }
  }  

bool Shape::areIntersecting( Side a, Side b, Level *world) {
	Vector* ptr_bounds = NULL;
	Vector bounds;
	bounds = world->GetBounds();
	ptr_bounds = &bounds;

	// a = side
	// b = ray

	float a_x1 = a.getA().GetX();
	float a_y1 = a.getA().GetY();
	float a_x2 = a.getB().GetX();
	float a_y2 = a.getB().GetY();

	float b_x1 = b.getA().GetX();
	float b_y1 = b.getA().GetY();
	float b_x2 = b.getB().GetX();
	float b_y2 = b.getB().GetY();

	float *m1, *m2, q1, q2, xc, yc, xm, ym;
	Point2D point_m, point_c, point_r, point_k1, point_k2;

	float 
		a_x_max, a_x_min, a_y_max, a_y_min,
		b_x_max, b_x_min, b_y_max, b_y_min;

	VECTOR_VALUE_TYPE
		a_distance_x_left, a_distance_x_right,
		a_distance_y_up, a_distance_y_down,
		b_distance_x_left, b_distance_x_right,
		b_distance_y_up, b_distance_y_down;

	Point2D 
		a_point_max, a_point_min,
		b_point_max, b_point_min;

	a_x_max = a_x1;
	a_x_min = a_x2;
	if ( a_x1 < a_x2) {
		a_x_max = a_x2;
		a_x_min = a_x1;
	}

	a_y_max = a_y1;
	a_y_min = a_y2;
	if ( a_y1 < a_y2 ) {
		a_y_max = a_y2;
		a_y_min = a_y1;
	}

	b_x_max = b_x1;
	b_x_min = b_x2;
	if ( b_x1 < b_x2) {
		b_x_max = b_x2;
		b_x_min = b_x1;
	}

	b_y_max = b_y1;
	b_y_min = b_y2;
	if ( b_y1 < b_y2 ) {
		b_y_max = b_y2;
		b_y_min = b_y1;
	}
	
	a_point_max = Point2D( a_x_max, a_y_max );
	a_point_min = Point2D( a_x_min, a_y_min );
	b_point_max = Point2D( b_x_max, b_y_max );
	b_point_min = Point2D( b_x_min, b_y_min );

	// y = m2*x + q = retta ray casting
	// y = m1*x + q = il lato

	m1 = NULL;
	m2 = NULL;
	q1 = a_x1;
	q2 = b_x1;

	if ( (a_x2 - a_x1) != 0 ) {
		m1 = new float;
		*m1 = (( a_y2 - a_y1 ) / ( a_x2 - a_x1 ));
		q1 = a_y1 - (*m1)*(a_x1);
	}
	if ( (b_x2 - b_x1) != 0 ) {
		m2 = new float;
		*m2 = (( b_y2 - b_y1 ) / ( b_x2 - b_x1 ));
		q2 = b_y1 - (*m2)*(b_x1);
	}

	// rette coincidenti o parallele verticali
	if ( ( m1 == NULL ) && ( m2 == NULL ) ) {
		if (a_x1 == b_x1) {

		float distance_bmax_up;
		float distance_bmax_down;
		float distance_bmin_up;
		float distance_bmin_down;
		
		GetOffSet( &distance_bmax_up, b_point_max, a_point_max, 1, ptr_bounds );
		GetOffSet( &distance_bmax_down, b_point_max, a_point_min, 1, ptr_bounds );
		GetOffSet( &distance_bmin_up, b_point_min, a_point_max, 1, ptr_bounds );
		GetOffSet( &distance_bmin_down, b_point_min, a_point_min, 1, ptr_bounds );

		if ( (distance_bmax_down <= 0 && distance_bmax_up >= 0) ||
			distance_bmin_down <= 0 && distance_bmin_up >= 0 ) {
				return true;
			}
		else return false;
			
			// float distance_a;
			// float distance_bmax;
			// float distance_bmin;

			// GetOffSet( &distance_a, a_point_min, a_point_max, 1, ptr_bounds );
			// GetOffSet( &distance_bmax, b_point_max, a_point_max, 1, ptr_bounds );
			// GetOffSet( &distance_bmin, b_point_min, a_point_max, 1, ptr_bounds );

			// if ( (distance_bmax >= 0 && distance_bmax <= distance_a) || (distance_bmin >= 0 && distance_bmin <= distance_a)) {
			// 	return true;
			// }
			// else {
			// 	return false;
			// }
			// a_y_min <= b_y1 <= a_y_max || a_y_min <= b_y2 <= a_y_max
		}
		else {
			return false;
		}
	}
	// retta A verticale
	else if ( m1 == NULL ) {

		xc = a_x1;
		yc = (*m2)*(xc) + q2;
		point_c = Point2D(xc,yc);

	}
	// retta B verticale
	else if ( m2 == NULL ) {

		xc = b_x1;
		yc = (*m1)*(xc) + q1;
		point_c = Point2D(xc,yc);

	}
	// rette parallele o coincidenti
	else if ( *m1 == *m2 ){
		return false;
		
	}

	// nessuna retta verticale
	else {
		xc = (q2 - q1) / (m1 - m2);
		yc = (*m1)*(xc) + q1;
		point_c = Point2D(xc,yc);

	}

		//pr punto estremo del raggio: può essere p1 o p2 in base al caso
		//raggio di point m e punto collisione deve essere inferiore o uguale al raggio di point m e pr (punto più estremo del raggio)
		world->GetNormalizedPoint(point_c);


		GetOffSet( &a_distance_x_left, point_c, a_point_min, 0, ptr_bounds );
		GetOffSet( &a_distance_x_right, point_c, a_point_max, 0, ptr_bounds );
		GetOffSet( &a_distance_y_up, point_c, a_point_max, 1, ptr_bounds );
		GetOffSet( &a_distance_y_down, point_c, a_point_min, 1, ptr_bounds );

		GetOffSet( &b_distance_x_left, point_c, b_point_min, 0, ptr_bounds );
		GetOffSet( &b_distance_x_right, point_c, b_point_max, 0, ptr_bounds );
		GetOffSet( &b_distance_y_up, point_c, b_point_max, 1, ptr_bounds );
		GetOffSet( &b_distance_y_down, point_c, b_point_min, 1, ptr_bounds );

		if ((a_distance_x_left <= 0) && (a_distance_x_right >= 0) &&
			(a_distance_y_down <= 0) && (a_distance_y_up >= 0) &&
			(b_distance_x_left <= 0) && (b_distance_x_right >= 0) &&
			(b_distance_y_down <= 0) && (b_distance_y_up >= 0)) {
			return true;
		}

		return false; 
	}

