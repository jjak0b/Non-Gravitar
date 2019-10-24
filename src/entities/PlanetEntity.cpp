#include "PlanetEntity.hpp"
#include "PlanetLevel.hpp"
#include "Player.hpp"


PlanetEntity::PlanetEntity( SolarSystem *world, Point2D origin, Bitmap *texture, unsigned int _radius, Vector _bounds ) : Entity( world, origin, texture, "PlanetEntity" ){
	this->radius = _radius;
	this->planet_level = new PlanetLevel( this, _bounds );


	this->escape_point = this->GetOrigin(); // origine pianeta + offset di ( 0, this->radius + 1 )
	this->escape_direction = Vector( this->escape_point.GetSize() );
	Vector default_escape_point_offset = Vector( this->escape_point.GetSize() );
	default_escape_point_offset.Set( 1, this->radius + 1 );
	this->escape_point.Add( default_escape_point_offset );

	this->shape = new Shape();
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
	/*else if( update_result ){
		// Mi interessa verificare solo la collisione con l'entità giocatore per verificare se vuole entrare nel pianeta
		Player *player = this->GetWorld()->GetPlayer();
		if( this->IsColliding( player ) ){
			this->Callback_OnCollide( game, player );
			update_result = false;
		}
	}*/

	return update_result;
}

void PlanetEntity::Draw( ViewPort *view ){
	if( IsDefined( this ) )
		DrawCircle( view, this->world, this->origin, this->radius, DEFAULT_PLANET_ENTITY_COLOR );
}

bool PlanetEntity::IsColliding( Entity *entity ){
	if( IsDefined(this) && IsDefined(entity) ){
		Vector bounds = this->GetWorld()->GetBounds();
		VECTOR_VALUE_TYPE dist_sqr = this->GetOrigin().DistanceSquared( entity->GetOrigin(), &bounds );
		return dist_sqr <= ( this->radius * this->radius );
	}
	return false;
}

void PlanetEntity::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	if( IsDefined( this ) && IsDefined( collide_ent ) ){
		/*if( !strcmp( collide_ent->GetClassname(), "Player" ) ){
			Player *player = (Player*)collide_ent;

			// il punto di fuga è vicino al punto di collisione ma distaccato dal punto di -2(direction) unità,
			// così che nel frame successivo alla fuga dal pianeta non sarà ancora eventualemente considerato come in collisione con esso ( anche se non può accadere )
	
			// inverto la direzione con la quale si è diretto verso il pianeta
			this->escape_direction = player->GetVelocity();
			this->escape_direction.Normalize();
			this->escape_direction.Scale( -1.0 );

			this->escape_point = collide_ent->GetOrigin();
			Vector escape_offset = this->escape_direction;
			escape_offset.Scale( 2.0 ); // Aggiungo un offset per esere sicuro di non tornare nuovamente nel raggio di collisioni del pianeta
			this->escape_point.Add( escape_offset );
			this->escape_point = this->GetWorld()->GetNormalizedPoint( this->escape_point );
			// Il giocatore entra nel Livello
			if( IsDefined( this->GetPlanetLevel() ) ){
				this->GetPlanetLevel()->AddEntity( player );
				// Creo il punto di atterraggio nel pianeta
				// GetMaxHeight() è il valore dell'altezza secondo cui si è considerati fuori dal pianeta,
				// quindi dovrà partire dal un'unità più in basso
				Point2D spawn_point = Point2D( 0, player->GetWorld()->GetMaxHeight() - 1 );
				player->SetOrigin( spawn_point );

				Vector direction = Vector( spawn_point.GetSize() );
				direction.Set( 1, -1 );
				VECTOR_VALUE_TYPE speed = player->GetSpeed();
				player->SetVelocity( Vector( direction.GetSize() ) ); // Azzero la velocità attuale, così la velocità iniziale sarà 0
				player->SetVelocity( direction.Scale( speed ) );

				game->SetCurrentLevel( this->GetPlanetLevel() );
			}
		}*/
	}
}
