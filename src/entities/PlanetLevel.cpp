    
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

	VECTOR_VALUE_TYPE half_width = this->GetMaxWidth() / 2;
	VECTOR_VALUE_TYPE linking_height = RANDOM_RANGE( min_point_distance_y, max_point_distance_y );

	Point2D start = Point2D( -half_width, linking_height );
	Point2D end = Point2D( half_width - 1 , linking_height );
	Vector direction = Vector( start.GetSize() );

	// temp è il punto che viene generato ed aggiunto alla lista
	list<Point2D> surface;
	Point2D
		temp = start,
		old_temp = temp;

	int random_prob_gen = 0;
	int min_prob_gen = 40;

	int random_prob_ent = 0;
	int which_ent = 0;

	// int min_prob_BunkerA = 50;
	// int min_prob_BunkerB = 50;
	// int min_prob_BunkerC = 50;
	// int min_prob_SmallFuel = 50;
	// int min_prob_BigFuel = 50;


	int prob_Bunker = 50;
	int bunker_Counter = 0;
	int fuel_Counter = 0;
	int max_Bunker = RANDOM_RANGE( 4, 8 );
	int max_Fuel = RANDOM_RANGE( 3 , 5 );
	

	// int BunkerA_counter = 0;
	// int BunkerB_counter = 0;
	// int BunkerC_counter = 0;
	// int BigFuel_counter = 0;
	// int SmallFuel_counter = 0;

	while( temp.GetX() < end.GetX() ){
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


		
		old_temp = temp;

		random_prob_gen = RANDOM_RANGE(0, 100);
		if (random_prob_gen <= min_prob_gen ) {
			random_prob_ent = RANDOM_RANGE(0, 100);
			if ( (random_prob_ent <= prob_Bunker) && (bunker_Counter < max_Bunker) ) {

				which_ent = RANDOM_RANGE(0, 4);
				if ( which_ent == 1 ) {
					this->AddEntity( new BunkerA(this,temp));
				}
				else if ( which_ent == 2) {
					this->AddEntity( new BunkerB(this, temp));
				}
				else {
					this->AddEntity( new BunkerC(this, temp) );
				}

				bunker_Counter++;
				prob_Bunker = prob_Bunker - 20;
			}
		else if( fuel_Counter < max_Fuel ) {
			which_ent = RANDOM_RANGE(0, 3);

			if ( which_ent == 1 ) {
					this->AddEntity( new SmallFuel(this,temp));
				}
			else if ( which_ent == 2) {
					this->AddEntity( new BigFuel(this, temp));
			}

			fuel_Counter++;
			prob_Bunker = prob_Bunker + 20;

		}	
			
		}
		else min_prob_gen = min_prob_gen + 5;
	}
	this->shape->addOffset( end, origin );
	
	}

Point2D PlanetLevel::RandomPoint() {

	list<Point2D> surface_points = this->shape->getAbsolutes();
	std::list<Point2D>::iterator it_begin = surface_points.begin();
	std::list<Point2D>::iterator it_end = surface_points.end();

	std::list<Point2D>::iterator it_pre_random_A = this->random_element(it_begin, it_end);
	std::list<Point2D>::iterator it_random_A = it_pre_random_A++;
	std::list<Point2D>::iterator it_post_random_A = it_random_A++;

	Point2D pre_random_A = (*(it_pre_random_A));
	Point2D random_A = (*(it_random_A));
	Point2D post_random_A = (*(it_post_random_A));

	int random_A_height = random_A.GetY();
	int pre_random_A_height = pre_random_A.GetY();
	int post_random_A_height = post_random_A.GetY();
	
	if (random_A_height < pre_random_A_height || random_A_height < post_random_A_height ) random_A.SetY(random_A.GetY() + 3);
	if (random_A_height < pre_random_A_height && random_A_height < post_random_A_height ) random_A.SetY(random_A.GetY() + 3);

	return random_A;
}


std::list<Point2D>::iterator PlanetLevel::random_element(std::list<Point2D>::iterator begin, std::list<Point2D>::iterator end) {
   
	const unsigned long n = std::distance(begin, end);
    const unsigned long divisor = (RAND_MAX + 1) / n;

    unsigned long k;
    do { k = std::rand() / divisor; } while (k >= n);

    std::advance(begin, k);
    return begin;
}

void PlanetLevel::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	
}