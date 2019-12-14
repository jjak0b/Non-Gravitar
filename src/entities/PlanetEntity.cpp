#include "PlanetEntity.hpp"
#include "PlanetLevel.hpp"
#include "Player.hpp"
#include "shared/Utility.h"

PlanetEntity::PlanetEntity( SolarSystem *world, Point2D origin, Bitmap *texture, unsigned int _radius, Vector _bounds ) : Entity( world, origin, texture, "PlanetEntity" ){
	this->radius = _radius;
	this->planet_level = new PlanetLevel( this, _bounds );


	this->escape_point = this->GetOrigin(); // origine pianeta + offset di ( 0, this->radius + 1 )
	this->escape_direction = Vector( this->escape_point.GetSize() );
	Vector default_escape_point_offset = Vector( this->escape_point.GetSize() );
	default_escape_point_offset.Set( 1, this->radius + 1 );
	this->escape_point.Add( default_escape_point_offset );

	this->shape = new Shape();
	
	this->enableCollisionLevelDetection = false;
}

PlanetEntity::~PlanetEntity(){}

void PlanetEntity::Delete( GameEngine* game ){
	if( !this->IsGarbage() ){
		if( IsDefined( this->planet_level ) ){
			this->planet_level->Delete( game ); // questo livello verrà aggiunto al garbage collector
			this->planet_level = NULL;
		}
		this->Entity::Delete( game );
	}
}

PlanetLevel *PlanetEntity::GetPlanetLevel(){
	return this->planet_level;
}

void PlanetEntity::SetPlanetLevel( PlanetLevel *planet_world ){
	this->planet_level = planet_world;
}

bool PlanetEntity::Update( GameEngine *game ){
	bool update_result = this->Entity::Update( game ); // Update Fondamentale

	// il giocatore ha liberato il pianeta, quindi possiamo considerare questo livello come garbage, quindi non sarà più accessibile da questo frame
	if( IsDefined( this->GetPlanetLevel() ) && this->GetPlanetLevel()->IsGenerated() && this->GetPlanetLevel()->IsFree() ){
		Player *player = this->GetWorld()->GetPlayer();
		player->AddScore( PLAYER_SCORE_PLANET_DESTROYED );
		update_result = false;
		this->Delete( game ); // Il Planetlevel associato e questa entità non saranno più significativi
	}

	return update_result;
}

void PlanetEntity::Draw( ViewPort *view ){
	if( IsDefined( this ) )
		DrawCircle( view, this->world, this->origin, this->radius, DEFAULT_PLANET_ENTITY_COLOR );
}

bool PlanetEntity::IsColliding(
#ifdef DEBUG_COLLISION_DRAWING
								GameEngine* game,
#endif
								Entity *entity ){

	if( IsDefined(this) && IsDefined(entity) ){
		Vector bounds = this->GetWorld()->GetBounds();
		VECTOR_VALUE_TYPE dist_sqr = this->GetOrigin().DistanceSquared( entity->GetOrigin(), &bounds );
		return dist_sqr <= SQR(this->radius);
	}
	return false;
}
