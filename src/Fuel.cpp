#include "Fuel.hpp"
#include "Entity.hpp"

Fuel::Fuel( Level *world, Point2D origin,  double size) : Entity( world, origin, NULL, "Fuel" ){
	this->size = size;
	this->origin = origin;
	this->world = world;
}

void Fuel::setSize(int size) {
	this->size = size;
};

int Fuel::getSize() {
	return this->size;
};