#include "BunkerC.hpp"
#include "engine/GameEngine.hpp"

#define BUNKERC_FIRE_DELAY 1.5

BunkerC::BunkerC( Level *world, Point2D origin) : Bunker(world, origin, BUNKER_HEALTH, "BunkerC"){

    this->texture = new Bitmap( 2, 6, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = "  _\xDC_ ";
	const BITMAP_DATA_TYPE raw_texturer1[] = " /\xDF\xDF\xDF\\";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1};
	this->texture->Load( rawtexture, NULL, 2, 6 );

	this->shape = new Shape();
	this->shape->addOffset(Point2D( -2, 0 ), origin);
	this->shape->addOffset(Point2D( +2, 0 ), origin);
	this->shape->addOffset(Point2D( +2, +2 ), origin);
	this->shape->addOffset(Point2D( -2, +2 ), origin);
}


bool BunkerC::Update(GameEngine* game) {
    
    bool update_result = this->Bunker::Update( game );

   if (update_result) {
	
	// Genera due proiettili nella stessa direzione.
		if ((game->GetTime() - this->timer) >= BUNKERC_FIRE_DELAY ) {

			Vector direction = Vector();
			
			direction.Set(0,0);
			direction.Set(1,1);
			Point2D projectile_origin = Point2D(this->origin.GetX(), this->origin.GetY() +2 );
			Shoot(projectile_origin, direction);
			count_projectile_fired++;

			if( count_projectile_fired < 2 ) {
				this->timer += 4*FRAME_TIME; // aspetta altri 4 frame prima di risparare
			}
			else{
				count_projectile_fired = 0;
				this->timer = game->GetTime();;
			}
		}

    }
    return update_result;
}