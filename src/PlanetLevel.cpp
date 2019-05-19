#include "PlanetLevel.hpp"
#include "PlanetEntity.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"

PlanetLevel::PlanetLevel( PlanetEntity *planet_entity, unsigned int max_longitude, unsigned int max_altitude ) : Level( max_longitude, max_altitude, "PlanetLevel"){
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
	printf("PlanetLevel UPDATE START\n");
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
			printf("SetCurrentLevel ->%s\n", solar_system->GetClassname() );
			system("pause");
			update_result = false;
		}
	}
	printf("PlanetLevel UPDATE END %d\n", update_result );
	return update_result;
}

bool PlanetLevel::IsFree(){
	list<Entity*> bunkers = this->GetEntities("Bunker", false, true );
	bool isFree = bunkers.empty();
	bunkers.clear();
	return isFree;
}

void PlanetLevel::Generate( GameEngine *game ){
	// temp per linea di testing
	Point2D start = Point2D( this->GetMaxWidth()/2.0, this->GetMaxHeight() / 2.0 );
	Point2D end = start;
	end.Add( Point2D( 10, 0 ) );
	this->surface.push_front( start );
	this->surface.push_front( end );
}