#include "BunkerB.hpp"
#include "engine/GameEngine.hpp"
    
BunkerB::BunkerB( Level *world, Point2D origin) : Bunker( world, origin, 300, "BunkerB"){

   this->texture = new Bitmap( 3, 8, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = " \xDC  \xDC  \xDC";
	const BITMAP_DATA_TYPE raw_texturer1[] = "  \\_|_/ ";
	const BITMAP_DATA_TYPE raw_texturer2[] = "  /\xDB\xDB\xDB\\ ";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1, raw_texturer2 };
	this->texture->Load( rawtexture, NULL, 3, 8 );

	this->shape = new Shape();
	this->shape->addOffset(Point2D( -2, -2 ), origin);
	this->shape->addOffset(Point2D( +2, -2 ), origin);
	this->shape->addOffset(Point2D( +3, +3 ), origin);
	this->shape->addOffset(Point2D( -3, +3 ), origin);
}


bool BunkerB::Update(GameEngine* game) {
    bool update_result = this->Bunker::Update( game );
	Vector direction;
	Point2D projectile_origin;
	
    if (update_result) {

		// Genera tre proiettili con tre direzioni diverse.
		if ((game->GetTime() - this->timer) >= 3) {

			direction.Set(0,-1);
			direction.Set(1,1);
			projectile_origin = Point2D(this->origin.GetX() -3, this->origin.GetY() +5 );
			Shoot( projectile_origin, direction);
			
			direction.Set(0,0);
			direction.Set(1,1);
			projectile_origin = Point2D(this->origin.GetX(), this->origin.GetY() +5 );
			Shoot(projectile_origin, direction);
			
			direction.Set(0,1);
			direction.Set(1,1);
			projectile_origin = Point2D(this->origin.GetX() +3, this->origin.GetY() +5 );
			Shoot(projectile_origin, direction);

			this->timer = game->GetTime();
		}
	}
    return update_result;
}




