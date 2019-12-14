#include "PlayerBeam.hpp"


PlayerBeam::PlayerBeam( Level *world, Point2D origin, Vector direction, VECTOR_VALUE_TYPE speed ) : Projectile( world, origin, direction, 0, "Beam_Projectile", speed, 4 ){
	fx = new Beam_FX(world, origin);
};

bool PlayerBeam::Update(GameEngine *game) {
	bool update_result = this->Projectile::Update(game);

	// Aggiornamento texture del raggio.
	if (update_result ){
		if ( this->fx != NULL )
			this->fx = this->fx->Add(origin);
	}
	else{
		if ( this->fx != NULL ){
			this->fx->Delete(game);
			this->fx = NULL;
		}
	}

	return update_result;
}

void PlayerBeam::Delete( GameEngine *game ){
	if( this->fx != NULL ){
		this->fx->Delete( game );
	}
	Projectile::Delete( game );
}