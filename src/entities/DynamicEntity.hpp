#pragma once

#include "Entity.hpp"

/**
 * @brief Entità che implementa il moto uniformemente accelerato
 * Ogni metodo auto eplicita il suo funzionamento
 */
class DynamicEntity : public Entity{
protected:
	Vector* previous_origin = NULL;
	Vector* velocity = NULL;
	Vector* previous_velocity = NULL;
	Vector* acceleration = NULL;
	VECTOR_VALUE_TYPE speed_max = 0;

public:
	DynamicEntity(Level *world, Point2D origin, Bitmap *texture, const char classname[] = "DynamicEntity", VECTOR_VALUE_TYPE speed_max = 1.0 );

	virtual ~DynamicEntity();

	VECTOR_VALUE_TYPE GetSpeed();

	VECTOR_VALUE_TYPE GetMaxSpeed();

	virtual Point2D SetOrigin( const Point2D origin );

	void SetVelocity(const Vector velocity);

	Vector GetVelocity();

	Vector GetAcceleration();

	void SetAcceleration(Vector acceleration);

	void AddAcceleration(Vector acceleration);

	virtual bool Update( GameEngine *game );

};
