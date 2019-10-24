#include "Beam.hpp"


Beam::Beam( Level *world, Point2D origin, Vector direction ) : Projectile( world, origin, direction, 0, "Beam_Projectile", 55, 4 ){
	fx = new Beam_FX(world, origin);
};

bool Beam::Update(GameEngine *game) {
	bool update_result = this->Projectile::Update(game);

	// Aggiornamento texture del raggio.
	if (update_result)
		this->fx->addNext(origin);
	else
		this->fx->Delete(game);

	return update_result;
}