#include "SmallFuel.hpp"

SmallFuel::SmallFuel( Level *world, Point2D origin) : Fuel( world, origin) {
    
    this->size = 50;

	this->texture = new Bitmap( 1, 4, COLOR_BLUE );
	const BITMAP_DATA_TYPE raw_texturer0[] = " [\xFE]";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0 };
	this->texture->Load( rawtexture, NULL, 1, 4 );

	this->GetShape()->addOffset(Point2D( -1, 0 ));
	this->GetShape()->addOffset(Point2D( +1, 0 ));
	this->GetShape()->addOffset(Point2D( -1, +2 ));
	this->GetShape()->addOffset(Point2D( +1, +2 ));
}

bool SmallFuel::Update(GameEngine *game) {
	bool update_result = Fuel::Update( game );
	return update_result;
}
