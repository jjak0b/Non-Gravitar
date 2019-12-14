#include "Shape.hpp"
#include "Segment.hpp"

Shape::Shape() {
};

Shape::~Shape() {
  this->absolute_points.clear();
  this->offset_points.clear();
};


void Shape::addAbsolute( Point2D point, ShapeAddOffsetOption option ) {
	switch ( option ){
		case ADD_BACK:
			this->absolute_points.push_back(point);
			break;
		default:
			this->absolute_points.push_front(point);
			break;
	}
}

void Shape::addOffset( Point2D point, Point2D origin, ShapeAddOffsetOption option ) {
	switch ( option ){
		case ADD_BACK:
			this->offset_points.push_back(point);
			break;
		default:
			this->offset_points.push_front(point);
			break;
	}
	
	VECTOR_VALUE_TYPE
		x = point.GetX(),
		y = point.GetY();

	// Mi tengo traccia del bounding box della figura
	if ( x < this->min_offset.GetX() )
		this->min_offset.SetX( x );
	if ( x > this->max_offset.GetX() )
		this->max_offset.SetX( x );
	if ( y < this->min_offset.GetY() )
		this->min_offset.SetY( y );
	if ( y > this->max_offset.GetY() )
		this->max_offset.SetY( y );

	origin.Add(point);
	addAbsolute(origin, option );
}

Point2D Shape::PopOffset( ShapeAddOffsetOption option ){
	Point2D offset;
	switch ( option ){
		default :
			this->absolute_points.pop_front();
			offset = this->offset_points.front();
			this->offset_points.pop_front();
			break;
		case ADD_BACK:
			this->absolute_points.pop_back();
			offset = this->offset_points.back();
			this->offset_points.pop_back();
			break;
	}

	return offset;
}

size_t Shape::GetOffsetCount(){
	return this->offset_points.size();
}

list<Point2D> Shape::getAbsolutes() {
  return this->absolute_points;
}
list<Point2D> Shape::getOffsetPoints() {
  return this->offset_points;
}

void Shape::UpdateAbsolutes( Point2D origin ) {
    Point2D point;
    list<Point2D>::iterator it_offset, it_absolute;
    it_offset = this->offset_points.begin();
    it_absolute = this->absolute_points.begin();
    
    for (; it_offset != this->offset_points.end(); it_offset++, it_absolute++ ) {
      point = origin;
      point.Add(*it_offset);
      
      (*it_absolute) = point;
    }
}

// Intersezioni
bool Shape::IsShapeColliding(
#ifdef DEBUG_COLLISION_DRAWING
								GameEngine* game,
#endif
								Point2D this_origin, Point2D shape_origin, Shape* collision_shape, Vector* bounds ) {

	Vector distance_offset;
	distance_offset = BuildDirection( this_origin, shape_origin, bounds );

	Point2D origin = Point2D(0,0);
	this->UpdateAbsolutes(origin);
	origin.Add(distance_offset);
	collision_shape->UpdateAbsolutes(origin);

	bool is_Colliding = false;
	list<Point2D> collision_points = collision_shape->getAbsolutes();
	std::list<Point2D>::iterator it;

	Point2D
		this_start,
		this_end,
		shape_start,
		shape_end;
	Segment
		side_of_this_shape,
		side_of_shape;
	std::list<Point2D>::iterator it_this = this->absolute_points.begin();
	this_start = this->absolute_points.back();
	while(
#ifndef DEBUG_COLLISION_DRAWING
			!is_Colliding &&
#endif
			it_this != this->absolute_points.end() ){
		this_end = *it_this;
		side_of_this_shape = Segment( this_start, this_end );

		it = collision_points.begin();
		shape_start = collision_points.back();
		while(
#ifndef DEBUG_COLLISION_DRAWING
				!is_Colliding &&
#endif
				it != collision_points.end() ){
			shape_end = *it;

			side_of_shape = Segment( shape_start, shape_end, bounds );
			is_Colliding = is_Colliding || side_of_this_shape.IsIntersecting(
#ifdef DEBUG_COLLISION_DRAWING
					game,
#endif

					side_of_shape );
			shape_start = shape_end;
			it++;
		}

		this_start = this_end;
		it_this++;
	}

	return	is_Colliding;
}
