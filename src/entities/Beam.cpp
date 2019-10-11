#include "Beam.hpp"

Beam::Beam( Level *world, Point2D origin) : Entity(world, origin ,NULL, "Beam"){
	
		this->texture = new Bitmap( 1, 1, COLOR_BLUE );
		const BITMAP_DATA_TYPE raw_texturer0[] = "\xB1";
		const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0};
		this->texture->Load( rawtexture, NULL, 1, 1);
}

void Beam::addNext( Point2D origin ) {
	if (this->next != NULL) this->next->addNext( origin );
	else this->next = new Beam(world, origin);
}

void Beam::Delete(GameEngine *game) {
	if (this->next != NULL) this->next->Delete(game);
	Entity::Delete(game);
}



