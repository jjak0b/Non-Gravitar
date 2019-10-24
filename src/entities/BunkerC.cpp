#include "BunkerC.hpp"
#include "engine/GameEngine.hpp"
    
BunkerC::BunkerC( Level *world, Point2D origin) : Bunker( world, origin, 300, "BunkerC"){

    this->texture = new Bitmap( 2, 6, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = "  _\xDC_ ";
	const BITMAP_DATA_TYPE raw_texturer1[] = " /\xDF\xDF\xDF\\";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1};
	this->texture->Load( rawtexture, NULL, 2, 6 );

	this->shape = new Shape();
	this->shape->addOffset(Point2D( -2, -1 ), origin);
	this->shape->addOffset(Point2D( +2, -1 ), origin);
	this->shape->addOffset(Point2D( +2, +2 ), origin);
	this->shape->addOffset(Point2D( -2, +2 ), origin);
}


bool BunkerC::Update(GameEngine* game) {
    
    bool update_result = this->Bunker::Update( game );

   if (update_result) {
	
	// Genera due proiettili nella stessa direzione.
		if ((game->GetTime() - this->timer) >= 1.5) {

			Vector *direction = new Vector();
			
			direction->Set(0,0);
			direction->Set(1,1);
			Point2D projectile_origin = Point2D(this->origin.GetX(), this->origin.GetY() +2 );
			Shoot(projectile_origin, (*direction));
			
			delete direction;

			if ((game->GetTime() - this->timer) >= 1.6) this->timer = game->GetTime();;
		}

    }
    return update_result;
}