#include "Segment.hpp"
#include <stddef.h>
#include <cmath>
#include <utility>
#include "Utility.h"
#include "Engine/GameConfig.h"

#ifdef DEBUG_COLLISION_DRAWING
#include "Engine/Viewport.hpp"
#include "Engine/GameEngine.hpp"
#endif

Segment::Segment(Point2D start, Point2D end, Vector* bounds ){
	this->start = start;
	this->end = end;
	evaluate( bounds );
}

Point2D Segment::GetStart() {
	return this->start;
}

Point2D Segment::GetEnd() {
	return this->end;
}

void Segment::evaluate(Vector* bounds ){
	VECTOR_VALUE_TYPE difference_x, difference_y, temp;
	GetOffSet( &difference_x, start, end, 0, bounds );
	GetOffSet( &difference_y, start, end, 1, bounds );


	if ( difference_x != 0 ) {
		m = difference_y / difference_x ;
		q =  ( (end.GetX()*start.GetY()) - (start.GetX()*end.GetY()) ) / difference_x;
		isVertical = false;
	}
	else{
		isVertical = true;
	}

	if( difference_y != 0 ){
		m_inverse = difference_x / difference_y ;
		isHorizontal = false;
	}
	else{
		isHorizontal = true;
	}
}

bool Segment::GetM( VECTOR_VALUE_TYPE* value, bool inverse ){

	if( inverse ){
		if( isHorizontal ){
			return false;
		}
		else{
			*value = m_inverse;
			return true;
		}
	}
	else{
		if( isVertical ){
			return false;
		}
		else{
			*value = m;
			return true;
		}
	}
}

bool Segment::GetQ( VECTOR_VALUE_TYPE* value ){
	if( isVertical ){
		return false;
	}
	else{
		*value = q;
		return true;
	}
}

bool Segment::IsVertical(){
	return isVertical;
}


bool Segment::IsHorizontal(){
	return isHorizontal;
}

bool Segment::IsIntersecting(
#ifdef DEBUG_COLLISION_DRAWING
								GameEngine* game,
#endif
								Segment segment ){


	bool check_point_on_segment = false;
	bool isIntersecting = false;
	VECTOR_VALUE_TYPE
			m1,
			m2,
			q1,
			q2,
			x,
			y;

	VECTOR_VALUE_TYPE
			this_x_min = this->start.GetX(),
			this_x_max = this->end.GetX(),
			segment_x_min = segment.start.GetX(),
			segment_x_max = segment.end.GetX(),
			this_y_min = this->start.GetY(),
			this_y_max = this->end.GetY(),
			segment_y_min = segment.start.GetY(),
			segment_y_max = segment.end.GetY();

	if (this_x_min > this_x_max) std::swap(this_x_min, this_x_max);
	if (this_y_min > this_y_max) std::swap(this_y_min, this_y_max);
	if (segment_x_min > segment_x_max) std::swap(segment_x_min, segment_x_max);
	if (segment_y_min > segment_y_max) std::swap(segment_y_min, segment_y_max);

	if (this_x_max < segment_x_min || segment_x_max < this_x_min
		|| this_y_max < segment_y_min || segment_y_max < this_y_min) {
		isIntersecting = false;
	}
	else if (this->IsVertical() && !segment.IsVertical()) {
		segment.GetM(&m2, false);
		segment.GetQ(&q2);
		x = this->start.GetX();
		y = (m2 * x) + q2;
		check_point_on_segment = true;
	}
	else if (segment.IsVertical() && !this->IsVertical()) {
		this->GetM(&m1, false);
		this->GetQ(&q1);
		x = segment.start.GetX();
		y = (m1 * x) + q1;
		check_point_on_segment = true;
	}
	else {
		this->GetM(&m1, false);
		this->GetQ(&q1);
		segment.GetM(&m2, false);
		segment.GetQ(&q2);

		if (m1 != m2) {
			x = (q2 - q1) / (m1 - m2);
			y = (m2 * x) + q2;
			check_point_on_segment = true;
		}
	}

	if (check_point_on_segment) {
		if (ISINRANGE(this_x_min, x, this_x_max) && ISINRANGE(segment_x_min, x, segment_x_max)
			&& ISINRANGE(this_y_min, y, this_y_max) && ISINRANGE(segment_y_min, y, segment_y_max)) {
			isIntersecting = true;
		}
	}
#ifdef DEBUG_COLLISION_DRAWING
	if( isIntersecting ){
		DrawCircle( game->GetViewport(), game->GetCurrentLevel(), Point2D( x, y ), 0, COLOR_ORANGE );
		DrawLine( game->GetViewport(), game->GetCurrentLevel(), segment.start, segment.end, COLOR_GREEN );
		DrawLine( game->GetViewport(), game->GetCurrentLevel(), this->start, this->end, COLOR_BLUE );
	}
#endif

	return isIntersecting;
}