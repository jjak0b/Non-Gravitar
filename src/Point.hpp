#pragma once

#include "Vector.hpp"

class Point : public Vector{
public:
	Point( unsigned int size = 2);

	/**
	 * @brief Effettua la distanza quadratica euclidea tra questo punto e P;
	 * restituisce -1 se i punti hanno dimensioni diverse
	 * PreCondition: p.GetSize() == GetSize();
	 * @param p 
	 * @return double 
	 */
	double DistanceSquared( Point p );

	/**
	 * @brief Effettua la distanza euclidea tra questo punto e P;
	 * restituisce -1 se i punti hanno dimensioni diverse
	 * PreCondition: p.GetSize() == GetSize();
	 * @param p 
	 * @return double 
	 */
	double Distance( Point p );
};

/**
 * @brief Restituisce il vettore direzione dal punto start a end
 * PreCondition: start.GetSize() == end.GetSize(), altrimenti verrà restituito un vettore con componenti nulle
 * @param start 
 * @param end 
 * @return Vector 
 */
Vector BuildDirection( Point start, Point end );