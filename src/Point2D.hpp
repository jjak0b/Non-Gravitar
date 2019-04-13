#pragma once

#include "Point.hpp"

class Point2D : public Point{
public:
	Point2D( int _x = 0, int _y = 0 );

	/**
	 * @brief Restituisce la componente X del vettore
	 */
	int GetX();

	/**
	 * @brief Imposta la componente X del vettore con il valore specificato
	 * @param value 
	 */
	void SetX( int value );

	/**
	 * @brief Restituisce la componente Y del vettore
	 */
	int GetY();

	/**
	 * @brief Imposta la componente Y del vettore con il valore specificato
	 * @param value 
	 */
	void SetY( int value );
};