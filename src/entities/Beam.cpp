#include "Beam.hpp"


Beam::Beam( Level *world, Point2D origin, Vector direction ) : Projectile( world, origin, direction, 0, "Beam_Projectile", 55, 4 ){

	texture = new Beam_FX(world, origin);
};

bool Beam::Update(GameEngine *game) {
	bool update_result = this->Projectile::Update(game);
	if (update_result) this->texture->addNext(origin);
	else this->texture->Delete(game);
	return update_result;
}