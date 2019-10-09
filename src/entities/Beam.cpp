#include "Beam.hpp"
#include "Projectile.hpp"
#include "Level.hpp"
#include "engine/GameEngine.hpp"
#include "Damageable.hpp"
#include "shared/Shape.hpp"
#include <cstring>
#include <iostream>
#include "Player.hpp"

Beam::Beam( Level *world, Point2D origin) : Entity(world, origin ,NULL, "Beam"){

		
		this->texture = new Bitmap( 1, 1, COLOR_BLUE );
		const BITMAP_DATA_TYPE raw_texturer0[] = "\xB1";
		const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0};
		this->texture->Load( rawtexture, NULL, 1, 1);

		
}




void Beam::addNext(  ) {
	Point2D next_origin =  Point2D(origin.GetX(), origin.GetY() -1 );
	if (this->next != NULL) this->next->addNext();
	else {
		Beam *b = new Beam(world, next_origin);
		this->next = b;
		}
	
}


void Beam::Kill(GameEngine *game) {
	
	if (this->next != NULL) {
		this->next->Kill(game);
		this->Delete(game);
	}
	else this->Delete(game);
}




