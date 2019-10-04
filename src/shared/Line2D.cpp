#include "Line2D.hpp"
#include <stddef.h>

Line2D::Line2D( Side segment, Vector* bounds ): Side( segment.GetStart(), segment.GetEnd() ){
	evaluate( bounds );
}

void Line2D::evaluate(Vector* bounds ){
	VECTOR_VALUE_TYPE difference_x, difference_y, temp;
	GetOffSet( &difference_x, start, end, 0, bounds );
	GetOffSet( &difference_y, start, end, 1, bounds );


	if ( difference_x != 0 ) {
		m = difference_y / difference_x ;
		GetUnitOffset(&q, m * start.GetX(), start.GetX(), 1, bounds ); // y - fx()
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

bool Line2D::GetM( VECTOR_VALUE_TYPE* value, bool inverse ){

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

bool Line2D::GetQ( VECTOR_VALUE_TYPE* value ){
	if( isVertical ){
		return false;
	}
	else{
		*value = q;
		return true;
	}
}

bool Line2D::IsVertical(){
	return isVertical;
}


bool Line2D::IsHorizontal(){
	return isHorizontal;
}

bool Line2D::IsIntersecting( Line2D line ){

	if( this->isVertical && line.isVertical ){
		if( this->start.GetX() == line.start.GetX() ){ // rette coincidenti
			return true;
		}
		else{ // rette parallele
			return false;
		}
	}
	else if( this->isVertical || line.isVertical ){
		return true;
	}
	else if( this->m == line.m ){ // rete paralle
		return false;
	}
	else{
		return true;
	}
}