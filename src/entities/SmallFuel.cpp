#include "SmallFuel.hpp"
#include "Player.hpp"

SmallFuel::SmallFuel( Level *world, Point2D origin) : Fuel( world, origin) {
    
    this->healthSize = 50;
    this->fuelSize = PLAYER_MAX_FUEL * 0.25;

	this->texture = new Bitmap( 1, 4, COLOR_BLUE );
	const BITMAP_DATA_TYPE raw_texturer0[] = " [\xFE]";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0 };
	this->texture->Load( rawtexture, NULL, 1, 4 );

	this->shape = new Shape();
	this->shape->addOffset(Point2D( -1, 0 ), origin);
	this->shape->addOffset(Point2D( +1, 0 ), origin);
	this->shape->addOffset(Point2D( +1, +2 ), origin);
	this->shape->addOffset(Point2D( -1, +2 ), origin);
}