#include "PlanetLevel.hpp"
#include "PlanetEntity.hpp"
#include "Player.hpp"
#include "BunkerA.hpp"
#include "BunkerB.hpp"
#include "BunkerC.hpp" 
#include "SmallFuel.hpp"
#include "BigFuel.hpp"
#include "shared/Utility.h"


PlanetLevel::PlanetLevel( PlanetEntity *planet_entity, Vector _bounds ) : Level( _bounds, "PlanetLevel"){
	this->planet_entity = planet_entity;
	this->shape = new Shape();
	generation_status = {
			.global_probability = 0,
			.info_bunkers = {
				.probability = {
						.min = 50,
						.max = 100,
						.value = 0
				},
				.count = {
					.min = 3,
					.value = 0
				}
			},
			.info_fuels = {
				.probability = {
					.min = 50,
					.max = 100,
					.value = 0
				},
				.count = {
					.min = 2,
					.value = 0
				}
			}
	};
	generation_status.info_bunkers.count.max = RANDOM_RANGE(
			generation_status.info_bunkers.count.min,
			GetMaxWidth() * ( 5 / 100) ); // al massimo il 5% dello spazio disponibile
	generation_status.info_fuels.count.max = RANDOM_RANGE(
			generation_status.info_fuels.count.min,
			generation_status.info_bunkers.count.max );
	
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

/**
 * @Brief:
 * Indica se il livello dovrebbe generarsi in asse X positiva o negativa rispetto all'origine;
 * Se è resituito 0 allora la telecamera è interna alla supercie generata
 * @param view
 * @return la distanza sull'asse x tra l'ultimo punto generato (nella direzione relativa al segno del valore restituito),
 * e il punto sul bordo della telecamera che "supera" tale punto
 */
int PlanetLevel::ShouldGenerate(ViewPort *view){
    VECTOR_VALUE_TYPE distance = 0;

    if( this->shape != NULL ) {
        Vector view_bounds = Vector( 2 );
        Point2D
            cameraOrigin = view->GetWorldOrigin(),
            cameraEdgeLeftOrigin = cameraOrigin,
            cameraEdgeRightOrigin = cameraOrigin;
        view_bounds.Set( BOUND_INDEX_WIDTH, view->GetWidth() );

        cameraEdgeRightOrigin.Add( view_bounds );
        cameraEdgeRightOrigin = GetNormalizedPoint( cameraEdgeRightOrigin );

        cameraEdgeLeftOrigin.Add( view_bounds.Scale( -1.0 ) );
        cameraEdgeLeftOrigin = GetNormalizedPoint( cameraEdgeLeftOrigin );

        list<Point2D> generated_points = this->shape->getAbsolutes();
        Point2D
            last_forward = generated_points.front(),
            last_backward = generated_points.back();

        Point2D cameraEdges[] = {
                cameraEdgeLeftOrigin,
                cameraEdgeRightOrigin
        };

        int i = 0;
        while( distance != 0 && i < 2 ) {
            if (cameraEdges[i].GetX() < GetMaxWidth() / 2.0) { // il bordo si trova nell prima metà
                GetOffSet(&distance, last_forward, cameraEdges[i], BOUND_INDEX_WIDTH, &bounds);
                if (distance < 0) // la camera precede l'ultimopunto
                    distance = 0;
            }
            else { // si trova nella seconda metà
                GetOffSet(&distance, last_backward, cameraEdges[i], BOUND_INDEX_WIDTH, &bounds);
                if (distance > 0) // la camera succede l'ultimopunto
                    distance = 0;
            }
            i++;
        }
    }
    return distance;
}

Entity* PlanetLevel::TryGenerateRandomEntity( Point2D spawnPoint ){
	int
		random_prob_ent = 0,
		which_ent = 0;
	bool spawned = false;
	Entity* entity = NULL;
	random_prob_ent = RANDOM_RANGE(0, 100);
	// Probabilità generazione Bunker
	if ( !spawned
		&& (this->generation_status.info_bunkers.count.value < this->generation_status.info_bunkers.count.max )
		&& (random_prob_ent <= this->generation_status.info_bunkers.probability.value)
		) {
		
		which_ent = RANDOM_RANGE(0, 3);
		switch( which_ent ){
			case 0:
				entity = new BunkerA(this, spawnPoint );
				break;
			case 1:
				entity = new BunkerB(this, spawnPoint );
				break;
			case 2:
				entity = new BunkerC(this, spawnPoint );
				break;
		}
		
		this->generation_status.info_bunkers.count.value++;
		this->generation_status.info_bunkers.probability.value = this->generation_status.info_bunkers.probability.min;
		spawned = true;
	}
	else{
		this->generation_status.info_bunkers.probability.value += 5;
	}
	
	// Probabilità generazione Fuel
	if( !spawned
		&& (this->generation_status.info_fuels.count.value < this->generation_status.info_fuels.count.max)
		&& (random_prob_ent <= this->generation_status.info_fuels.probability.value)
		) {
		which_ent = RANDOM_RANGE(0, 2);
		switch( which_ent ){
			case 0:
				entity = new SmallFuel(this, spawnPoint );
				break;
			case 1:
				entity = new BigFuel(this, spawnPoint );
				break;
		}
		
		this->generation_status.info_fuels.count.value++;
		this->generation_status.info_fuels.probability.value = this->generation_status.info_fuels.probability.min;
		spawned = true;
	}
	else{
		this->generation_status.info_fuels.probability.value += 10;
	}
	
	return entity;
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
	VECTOR_VALUE_TYPE linking_height = min_point_distance_y;

	Point2D start = Point2D( -half_width, linking_height );
	Point2D end = Point2D( half_width - 1 , linking_height );
	Vector direction = Vector( start.GetSize() );

	// temp è il punto che viene generato ed aggiunto alla lista
	list<Point2D> surface_empty;
	list<Point2D>::iterator temp_point;
	Point2D
		temp = start,
		old_temp = temp;
	
	Point2D midpoint = Point2D(0,0);
	
 
	if( shape->GetOffsetCount() < 2 ){
		shape->addOffset( Point2D(0,0), origin, ADD_FRONT );
		// shape->addOffset( end, origin, ADD_FRONT );
	}
	list<Point2D> generated_offsets = shape->getOffsetPoints();
	Point2D
		back = generated_offsets.back(),
		front = generated_offsets.front();
	
	VECTOR_VALUE_TYPE distance_generation;
	
	
	VECTOR_VALUE_TYPE dist;
	if( generated_offsets.size() > 1 ) {
		dist = front.DistanceSquared(back, &bounds);
		
		if (!back.Equals(front) && generated_offsets.size() > 20 ) {
			isGenerated = true;
		}
	}
	
	bool isPointGenerated = false;
	
	while( !isPointGenerated && !isGenerated && (distance_generation = ShouldGenerate( game->GetViewport() )) != 0 ) {
		
		// GENERAZIONE VERTICI DEL TERRENO
		generated_offsets = shape->getOffsetPoints();
		back = generated_offsets.back();
		front = generated_offsets.front();
		
        // sul back ci metto gli offset "positivi"
        if( distance_generation > 0 ) {
            old_temp = front;
        }
        // sul front ci metto gli offset "negativi"
        else if( distance_generation > 0 ) {
            old_temp = back;
        }
        
		
		// // PROBABILITA DI GENERAZIONE ENTITA SUL PUNTO GENERATO
		
		offset_x = RANDOM_RANGE(min_point_distance_x, max_point_distance_x);
		offset_y = min_point_height + RANDOM_RANGE(min_point_distance_y, max_point_distance_y);
		if (rand() % 100 < 50) { // scelgo se variare l'offset del punto in positivo o in negativo
			offset_y *= -1;
		}

		
		temp = old_temp;
		direction.Set(0, offset_x);
		direction.Set(1, offset_y);
		temp.Add(direction);

		// l'ordinata deve essere compresa tra min_point_height e max_point_height
		temp.SetY(
				max(
						min(temp.GetY(), max_point_height),
						min_point_height));
		//}while( temp.GetY() == old_temp.GetY() );
		
		GetOffSet(&offset_x , old_temp, temp, BOUND_INDEX_WIDTH,  &bounds);
		GetOffSet(&offset_y , old_temp, temp, BOUND_INDEX_HEIGHT,  NULL);
		midpoint = Point2D( (old_temp).GetX() + offset_x / 2.0, (old_temp).GetY() + offset_y / 2.0 );
	 
		if( distance_generation > 0  ){
			shape->addOffset( temp, origin, ADD_FRONT );
			isPointGenerated = true;
		}
		else if( distance_generation < 0  ){
			shape->addOffset( temp, origin, ADD_BACK );
			isPointGenerated = true;
		}
		
		
		if( isPointGenerated ){
			TryGenerateRandomEntity( midpoint );
		}
		
		//old_temp = temp;
	}
	
}

void PlanetLevel::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	
}