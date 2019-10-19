    
#include "PlanetLevel.hpp"
#include "PlanetEntity.hpp"
#include "engine/GameEngine.hpp"
#include "Player.hpp"
#include "BunkerA.hpp"
#include "BunkerB.hpp"
#include "BunkerC.hpp"
#include "Bunker.hpp"
#include "Projectile.hpp"
#include "Damageable.hpp"
#include <cmath>
#include "Level.hpp"
#include <ctime>    
#include <cstdlib>  
#include "Entity.hpp"
#include "shared/Point2D.hpp"
#include "Fuel.hpp"
#include "SmallFuel.hpp"
#include "BigFuel.hpp"
#include <cstring>
#include "shared/Utility.h"


PlanetLevel::PlanetLevel( PlanetEntity *planet_entity, Vector _bounds ) : Level( _bounds, "PlanetLevel"){
	this->planet_entity = planet_entity;
	this->shape = new Shape();
}

void PlanetLevel::Delete( GameEngine* game ){
	if( this->planet_entity != NULL ){
		this->planet_entity->SetPlanetLevel( NULL );
		this->planet_entity = NULL;
	}
	Level::Delete( game );
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
				// Il giocatore nel prossimo frame si deve trovare nel punto di fuga vicino a dove è si era diretto prima di entrare nel pianeta, e in direzione opposta
				Point2D spawn_point = this->GetPlanetEntity()->escape_point;
				_player->SetOrigin( spawn_point );

				Vector _player_velocity = this->GetPlanetEntity()->escape_direction;
				_player_velocity.Scale( _player->GetSpeed() );
				_player->SetVelocity( _player_velocity );

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
		min_point_distance_x = 7,
		max_point_distance_x = 17,
		min_point_distance_y = 3,
		max_point_distance_y = 11,
		max_point_height = (6.0/10.0)*this->GetMaxHeight(),
		min_point_height = 3;

	VECTOR_VALUE_TYPE 
		offset_x,
		offset_y;

	VECTOR_VALUE_TYPE half_width = this->GetMaxWidth() / 2.0;
	VECTOR_VALUE_TYPE linking_height = RANDOM_RANGE( min_point_distance_y, max_point_distance_y );

	Point2D start = Point2D( -half_width, linking_height );
	Point2D end = Point2D( half_width - 1 , linking_height );
	Vector direction = Vector( start.GetSize() );

	// temp è il punto che viene generato ed aggiunto alla lista
	list<Point2D> surface_empty;
	list<Point2D>::iterator temp_point;
	Point2D
		temp = start,
		old_temp = temp;

	int random_prob_gen = 40,
		min_prob_gen = 0,

		random_prob_ent = 0,
		which_ent = 0,

		prob_Bunker = 50,
		bunker_Counter = 0,
		fuel_Counter = 0,
		min_Fuel = 2,
		min_Bunker = 3,
		max_Bunker = RANDOM_RANGE( min_Bunker, 8 ),
		max_Fuel = RANDOM_RANGE( min_Fuel, max_Bunker );
	

	while( temp.GetX() < end.GetX() ){
		// GENERAZIONE VERTICI DEL TERRENO
		do {
			this->shape->addOffset(temp, origin);
			//surface.push_front(temp);
			offset_x = RANDOM_RANGE(min_point_distance_x, max_point_distance_x);
			offset_y = min_point_height + RANDOM_RANGE(min_point_distance_y, max_point_distance_y);
			if (rand() % 100 < 50) { // scelgo se variare l'offset del punto in positivo o in negativo
				offset_y *= -1;
			}

			direction.Set(0, offset_x);
			direction.Set(1, offset_y);

			temp.Add(direction);

			// l'ordinata deve essere compresa tra min_point_height e max_point_height
			temp.SetY(
					max(
							min(temp.GetY(), max_point_height),
							min_point_height));
		}while( temp.GetY() == old_temp.GetY() );

		// PROBABILITA DI GENERAZIONE ENTITA SUL PUNTO GENERATO
		random_prob_gen = RANDOM_RANGE(0, 100);
		if (random_prob_gen <= min_prob_gen ) {
			random_prob_ent = RANDOM_RANGE(0, 100);
			if ( (random_prob_ent <= prob_Bunker) && (bunker_Counter < max_Bunker) ) {

				which_ent = RANDOM_RANGE(0, 4);
				if ( which_ent == 1 ) {
					new BunkerA(this,temp);
				}
				else if ( which_ent == 2) {
					new BunkerB(this, temp);
				}
				else {
					new BunkerC(this, temp);
				}

				bunker_Counter++;
				prob_Bunker = prob_Bunker - 20;
			}
			else if( fuel_Counter < max_Fuel ) {
				which_ent = RANDOM_RANGE(0, 3);
				if ( which_ent == 1 ) {
					new SmallFuel(this,temp);
				}
				else if ( which_ent == 2) {
					new BigFuel(this, temp);
				}

				fuel_Counter++;
				prob_Bunker = prob_Bunker + 20;
			}			
		}
		else {
			surface_empty.push_front(temp);
			min_prob_gen = min_prob_gen + 5;
		}

		old_temp = temp;
	}
	this->shape->addOffset( end, origin );

	// DOPO LA GENERAZIONE DEL TERRENO TENTA LA GENERAZIONE DELLE ENTITA RIMASTE
	while ( bunker_Counter < min_Bunker && !surface_empty.empty() ) {
		temp_point = Utility::random_element(surface_empty.begin(), surface_empty.end());
		which_ent = RANDOM_RANGE(0, 4);
		if ( which_ent == 1 ) {
			new BunkerA(this,*temp_point);
		}
		else if ( which_ent == 2) {
			new BunkerB(this, *temp_point);
		}
		else {
			new BunkerC(this, *temp_point);
		}
		bunker_Counter++;
		surface_empty.erase(temp_point);
	}
	while ( fuel_Counter < min_Fuel && !surface_empty.empty() ) {
		temp_point = Utility::random_element(surface_empty.begin(), surface_empty.end());
		which_ent = RANDOM_RANGE(0, 3);
		if ( which_ent == 1 ) {
			new SmallFuel(this,*temp_point);
		}
		else if ( which_ent == 2) {
			new BigFuel(this, *temp_point);
		}
		fuel_Counter++;
		surface_empty.erase(temp_point);
	}
	
}

void PlanetLevel::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	
}