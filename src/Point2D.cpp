#include "Point2D.hpp"

Point2D::Point2D( VECTOR_TYPE _x, VECTOR_TYPE _y ) : Point( 2 ) {
	this->SetX( _x );
	this->SetY( _y );
}

int Point2D::GetX(){
	int value;
	this->Vector::Get( 0, &value );
	return value;
}

void Point2D::SetX( VECTOR_TYPE value ){
	this->Vector::Set( 0, value );
}

int Point2D::GetY(){
	int value;
	this->Vector::Get( 1, &value );
	return value;
}

void Point2D::SetY( VECTOR_TYPE value ){
	this->Vector::Set( 1, value );
}

void Point2D::Get( unsigned int i, VECTOR_TYPE *return_value ){
	Vector::Get( i, return_value );
}
void Point2D::Set( unsigned int i, VECTOR_TYPE value ){
	Vector::Set( i, value );
}