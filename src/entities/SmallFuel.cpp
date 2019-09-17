#include "SmallFuel.hpp"

SmallFuel::SmallFuel( Level *world, Point2D origin) : Fuel( world, origin) {
    
    this->size = 50;

	this->texture = new Bitmap( 1, 4, COLOR_BLUE );
	const BITMAP_DATA_TYPE raw_texturer0[] = " [\xFE]";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0 };
	this->texture->Load( rawtexture, NULL, 1, 4 );
}

bool SmallFuel::Update(GameEngine *game) {
	bool update_result = Fuel::Update( game );
	shapeUpdate();
	return update_result;
}

void SmallFuel::shapeUpdate() {

	(*this->GetShape()).deletePoints();

	Point2D a = Point2D(this->origin.GetX() -1, this->origin.GetY() );
    Point2D b = Point2D(this->origin.GetX() +1, this->origin.GetY() );
	Point2D c = Point2D(this->origin.GetX() -1, this->origin.GetY()  +2);
    Point2D d = Point2D(this->origin.GetX() +1, this->origin.GetY() +2);

	(*this->GetShape()).addPoint(c);
	(*this->GetShape()).addPoint(a);
	(*this->GetShape()).addPoint(b);
	(*this->GetShape()).addPoint(d);
}