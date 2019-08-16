#include "Point2D.hpp"

Point2D::Point2D( VECTOR_VALUE_TYPE _x, VECTOR_VALUE_TYPE _y ) : Point( 2 ) {
	this->SetX( _x );
	this->SetY( _y );
}

VECTOR_VALUE_TYPE Point2D::GetX(){
	VECTOR_VALUE_TYPE value;
	this->Vector::Get( 0, &value );
	return value;
}

void Point2D::SetX( VECTOR_VALUE_TYPE value ){
	this->Vector::Set( 0, value );
}

VECTOR_VALUE_TYPE Point2D::GetY(){
	VECTOR_VALUE_TYPE value;
	this->Vector::Get( 1, &value );
	return value;
}

void Point2D::SetY( VECTOR_VALUE_TYPE value ){
	this->Vector::Set( 1, value );
}

bool Point2D::Get( unsigned int i, VECTOR_VALUE_TYPE *return_value ){
	return Vector::Get( i, return_value );
}
bool Point2D::Set( unsigned int i, VECTOR_VALUE_TYPE value ){
	return Vector::Set( i, value );
}

