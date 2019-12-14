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

Beam_FX* Beam_FX::Add( Point2D origin ) {
	Beam_FX *head = new Beam_FX(world, origin);
	head->next = this;
	return head;
}

void Beam_FX::Delete(GameEngine *game) {
	Beam_FX *head = this;
	while( head != NULL ){
		head->Entity::Delete( game );
		head = head->next;
	}
}



