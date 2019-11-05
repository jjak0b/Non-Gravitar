#include "BigFuel.hpp"
#include "Player.hpp"
BigFuel::BigFuel( Level *world, Point2D origin) : Fuel( world, origin) {
    
	this->healthSize = PLAYER_HEALTH * 0.5;
	this->fuelSize = PLAYER_MAX_FUEL;
	
	this->texture = new Bitmap( 2, 4, COLOR_BLUE );
	const BITMAP_DATA_TYPE raw_texturer0[] = " \xC9\xDC\xBB";
	const BITMAP_DATA_TYPE raw_texturer1[] = " \xC8\xDF\xBC";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1};
	this->texture->Load( rawtexture, NULL, 2, 4 );
	
	this->shape = new Shape();
	this->shape->addOffset(Point2D( -1, 0 ), origin);
	this->shape->addOffset(Point2D( +1, 0 ), origin);
	this->shape->addOffset(Point2D( +1, +3), origin);
	this->shape->addOffset(Point2D( -1, +3 ), origin);
}