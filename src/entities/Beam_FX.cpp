#include "Beam_FX.hpp"

Beam_FX::Beam_FX( Level *world, Point2D origin) : Entity(world, origin ,NULL, "Beam_FX"){

	this->shape = NULL;
	this->texture = new Bitmap( 1, 1, COLOR_BLUE );
	const BITMAP_DATA_TYPE raw_texturer0[] = "\xB1";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0};
	this->texture->Load( rawtexture, NULL, 1, 1);
	
	this->isCollidable = false;
	this->enableCollisionLevelDetection = false;
}

void Beam_FX::addNext( Point2D origin ) {
	if (this->next != NULL)
		this->next->addNext( origin );
	else
		this->next = new Beam_FX(world, origin);
}

void Beam_FX::Delete(GameEngine *game) {
	if (this->next != NULL)
		this->next->Delete(game);
	Entity::Delete(game);
}



