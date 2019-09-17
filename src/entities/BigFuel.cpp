#include "BigFuel.hpp"

BigFuel::BigFuel( Level *world, Point2D origin) : Fuel( world, origin) {
    
	this->size = 100;

	this->texture = new Bitmap( 2, 4, COLOR_BLUE );
	const BITMAP_DATA_TYPE raw_texturer0[] = " \xC9\xDC\xBB";
	const BITMAP_DATA_TYPE raw_texturer1[] = " \xC8\xDF\xBC";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1};
	this->texture->Load( rawtexture, NULL, 2, 4 );
}

bool BigFuel::Update(GameEngine *game) {
	bool update_result = Fuel::Update( game );
	shapeUpdate();
	return update_result;
}


void BigFuel::shapeUpdate() {

	(*this->GetShape()).deletePoints();

	Point2D a = Point2D(this->origin.GetX() -1, this->origin.GetY() );
    Point2D b = Point2D(this->origin.GetX() +1, this->origin.GetY() );
	Point2D c = Point2D(this->origin.GetX() -1, this->origin.GetY()  +3);
    Point2D d = Point2D(this->origin.GetX() +1, this->origin.GetY() +3);

	(*this->GetShape()).addPoint(c);
	(*this->GetShape()).addPoint(a);
	(*this->GetShape()).addPoint(b);
	(*this->GetShape()).addPoint(d);
}
