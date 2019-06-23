#pragma once

#include "Point.hpp"

class Point2D : public Point{
public:
	Point2D( VECTOR_VALUE_TYPE _x = 0, VECTOR_VALUE_TYPE _y = 0 );

	/**
	 * @brief Restituisce la componente X del vettore
	 */
	VECTOR_VALUE_TYPE GetX();

	/**
	 * @brief Imposta la componente X del vettore con il valore specificato
	 * @param value 
	 */
	void SetX( VECTOR_VALUE_TYPE value );

	/**
	 * @brief Restituisce la componente Y del vettore
	 */
	VECTOR_VALUE_TYPE GetY();

	/**
	 * @brief Imposta la componente Y del vettore con il valore specificato
	 * @param value 
	 */
	void SetY( VECTOR_VALUE_TYPE value );

	protected:
	// override per non essere accessibile dall'esterno
	bool Get( unsigned int i, VECTOR_VALUE_TYPE *return_value );
	bool Set( unsigned int i, VECTOR_VALUE_TYPE value );
};