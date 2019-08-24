#pragma once

#include "Entity.hpp"

class DynamicEntity : public Entity{
protected:
	Vector* velocity = NULL;
	Vector* previous_velocity = NULL;
	Vector* acceleration = NULL;
	VECTOR_VALUE_TYPE speed_max = 0;

public:
	DynamicEntity(Level *world, Point2D origin, Bitmap *texture, const char classname[] = "DynamicEntity", VECTOR_VALUE_TYPE speed_max = 1.0 );

	virtual ~DynamicEntity();

	VECTOR_VALUE_TYPE GetSpeed();

	VECTOR_VALUE_TYPE GetMaxSpeed();

	void SetVelocity(const Vector velocity);

	Vector GetVelocity();

	Vector GetAcceleration();

	void SetAcceleration(Vector acceleration);

	void AddAcceleration(Vector acceleration);

	virtual bool Update( GameEngine *game );
};
