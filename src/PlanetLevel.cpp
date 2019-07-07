#include "PlanetLevel.hpp"
#include "PlanetEntity.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"
#include <cmath>

PlanetLevel::PlanetLevel( PlanetEntity *planet_entity, Vector _bounds ) : Level( _bounds, "PlanetLevel"){
	this->planet_entity = planet_entity;
}

PlanetLevel::~PlanetLevel(){
	this->Delete();
}

void PlanetLevel::Delete(){
	if( this->planet_entity != NULL ){
		this->planet_entity->SetPlanetLevel( NULL );
		this->planet_entity = NULL;
	}
	this->Level::Delete();
}

PlanetEntity *PlanetLevel::GetPlanetEntity(){
	return this->planet_entity;
}

void PlanetLevel::SetPlanetEntity( PlanetEntity *entity ){
	this->planet_entity = entity;
}

bool PlanetLevel::Update( GameEngine *game ){
	bool update_result = Level::Update( game );
	if( update_result ){
		if( IsDefined( this->GetPlayer() ) && this->GetPlayer()->IsOutOfTheWorld() ){
			SolarSystem *solar_system = NULL;
			if( IsDefined( this->GetPlanetEntity() ) ){
				solar_system = (SolarSystem*)this->GetPlanetEntity()->GetWorld();
				Player *_player = this->GetPlayer();
				if( IsDefined( solar_system ) ){
					solar_system->AddEntity( _player );
				}
				// Il giocatore nel prossimo frame si deve trovare nel punto di fuga vicino a dove è si era diretto prima di entrare nel pianeta
				Point2D spawn_point = this->GetPlanetEntity()->escape_point;
				_player->SetOrigin( spawn_point );
			}

			// Carica il sistema solare come prossimo livello del successivo frame
			// Nota facoltativa: solar_system dovrebbe essere sempre definito per come è stata impostata la logica di cambio di livello,
			// comunque nel caso esso non sia definito per un qualche motivo quale ad esempio un livello speciale o futuri cambiamenti
			// di comportamento dell'uscita del pianeta, sarà il frame dell'Engine principale a gestirsi il cambio di livello nel caso il livello cambiato non sia definito
			game->SetCurrentLevel( solar_system );
			update_result = false;
		}
	}
	return update_result;
}

bool PlanetLevel::IsFree(){
	list<Entity*> bunkers = this->GetEntities("Bunker", false, true );
	bool isFree = bunkers.empty();
	bunkers.clear();
	return isFree;
}

void PlanetLevel::Generate( GameEngine *game ){
	VECTOR_VALUE_TYPE
		min_point_distance_x = 4,
		max_point_distance_x = 15,
		min_point_distance_y = 3,
		max_point_distance_y = 8,
		max_point_height = (6.0/10.0)*this->GetMaxHeight(),
		min_point_height = 3;

	VECTOR_VALUE_TYPE 
		offset_x,
		offset_y;

	Point2D start = Point2D();
	Point2D end = start;
	end.SetX( this->GetMaxWidth() - 1 );
	Vector direction = Vector( start.GetSize() );

	// temp è il punto che viene generato ed aggiunto alla lista
	Point2D temp = start;
	while( temp.GetX() < end.GetX() ){
		this->surface.push_front( temp );
		offset_x = min_point_distance_x + (rand() % (int)(max_point_distance_x - min_point_distance_x));
		offset_y = min_point_distance_y + (rand() % (int)(max_point_distance_y - min_point_distance_y));
		if( rand() % 100 < 50 ){ // scelgo se variare l'offset del punto in positivo o in negativo
			offset_y *= -1;
		}
		direction.Set( 1, offset_y );
		direction.Set( 0, offset_x );
		temp.Add( direction );
		// temp.SetY( min_point_height + (temp.GetY() % (int)(max_point_height - min_point_distance_y) ) );
		// l'ordinata deve essere compresa tra min_point_height e max_point_height
		temp.SetY(
				max(
					min( temp.GetY(), max_point_height ),
					min_point_height ) );
	}
	this->surface.push_front( end );
}