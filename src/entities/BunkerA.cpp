#include "BunkerA.hpp"
#include "Bunker.hpp"
#include "Projectile.hpp"
#include "engine/GameEngine.hpp"
#include <ctime>
#include <cstring>

BunkerA::BunkerA( Level *world, Point2D origin) : Bunker( world, origin, 300, "BunkerA"){

    this->texture = new Bitmap( 2, 3, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = "q_p";
	const BITMAP_DATA_TYPE raw_texturer1[] = "/\xDB\\";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1};
	this->texture->Load( rawtexture, NULL, 2, 3);

	this->shape = new Shape();
	this->shape->addOffset(Point2D( -1, 0 ), origin);
	this->shape->addOffset(Point2D( +1, 0 ), origin);
	this->shape->addOffset(Point2D( -1, +2 ), origin);
	this->shape->addOffset(Point2D( +1, +2 ), origin);
}

bool BunkerA::Update(GameEngine* game) {
    bool update_result = Bunker::Update( game );

	if (update_result) {
		if ((game->GetTime() - this->timer) >= 2) {

			int r1 = random(4);
			int r2 = random (4);
			while (r1 == r2) r2 = random(4);

			Vector *direction = new Vector();
			direction->Set(0,r1);
			direction->Set(1,1);
			Point2D projectile_origin = Point2D(this->origin.GetX() -1, this->origin.GetY() +2 );
			Shoot( projectile_origin, (*direction));

			direction->Set(0,r2);
			direction->Set(1,1);
			projectile_origin = Point2D(this->origin.GetX() +1, this->origin.GetY() +2 );
			Shoot( projectile_origin, (*direction));

			delete direction;

			this->timer = game->GetTime();
    	}


    }
	return update_result;
	
	
}



void BunkerA::Draw( ViewPort *view ){
	Bunker::Draw( view );
}