#include "BunkerA.hpp"
#include "engine/GameEngine.hpp"

BunkerA::BunkerA( Level *world, Point2D origin) : Bunker(world, origin, BUNKER_HEALTH, "BunkerA"){

    this->texture = new Bitmap( 2, 3, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = "q_p";
	const BITMAP_DATA_TYPE raw_texturer1[] = "/\xDB\\";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1};
	this->texture->Load( rawtexture, NULL, 2, 3);

	this->shape = new Shape();
	this->shape->addOffset(Point2D( -1, 0 ), origin);
	this->shape->addOffset(Point2D( +1, 0 ), origin);
	this->shape->addOffset(Point2D( +1, +2 ), origin);
	this->shape->addOffset(Point2D( -1, +2 ), origin);
}

bool BunkerA::Update(GameEngine* game) {
    bool update_result = Bunker::Update( game );
	Vector direction;
	Point2D projectile_origin;
	int r1 = 0,
		r2 = 0;

	if (update_result) {

		// Genera due proiettili con direzione casuale.
		if ((game->GetTime() - this->timer) >= 2) {

			r1 = rand() % 9 + (-4);
			int r2 = rand() % 9 + (-4);
			while (r1 == r2) r2 = rand() % 9 + (-4);

			direction.Set(0,r1);
			direction.Set(1,1);
			projectile_origin = Point2D(this->origin.GetX() -1, this->origin.GetY() +2 );
			Shoot( projectile_origin, direction);

			direction.Set(0,r2);
			direction.Set(1,1);
			projectile_origin = Point2D(this->origin.GetX() +1, this->origin.GetY() +2 );
			Shoot( projectile_origin, direction);

			this->timer = game->GetTime();
    	}
    }
	return update_result;	
}