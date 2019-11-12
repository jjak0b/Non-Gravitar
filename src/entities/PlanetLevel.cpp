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
			.info_bunkers = {
				.probability = {
						.min = 40,
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
					.min = 40,
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

    generation_status.info_surface = {
			.distance_x = {
				.min = 7,
				.max = 13,
				.value = 0
			},
			.distance_y = {
				.min = 3,
				.max = 11,
				.value = 0
			},
			.bound_y = {
				.min = 3,
				.max = ((VECTOR_VALUE_TYPE)this->GetMaxHeight()) * (VECTOR_VALUE_TYPE)(6.0/10.0),
				.value = 0
			},
			.isGeneratingNegativeDone = false,
			.isGeneratingPositiveDone = false
    };
	
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

bool PlanetLevel::IsFree() {
	bool isFree = isGenerated;
	list<Entity*> bunkers = this->GetEntities("Bunker", false, true );
	isFree = isFree && bunkers.empty();
	bunkers.clear();
	return isFree;
}

// TODO: remove
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
	if( !isGenerated && shape != NULL ) {
		bool isPointGenerated = false;

		ViewPort* view = game->GetViewport();

		VECTOR_VALUE_TYPE
			half_width = (double)this->GetMaxWidth() / 2.0,
			linking_height = generation_status.info_surface.bound_y.min,
			offset_x,
			offset_y,
			distance_required = 0;

		Point2D
			start_link = Point2D( -half_width, linking_height ),
			end_link = Point2D( half_width, linking_height ),
			temp,
			old_temp,
			midpoint,
			last_relative_positive,
			last_relative_negative,
			last_absolute_positive,
			last_absolute_negative;

		list<Point2D> generated_relative_points;

		if( shape->GetOffsetCount() < 4 ){
			generated_relative_points = shape->getOffsetPoints();
			Point2D
				start_positive = Point2D(0, linking_height ),
				start_negative = Point2D(0, linking_height );
			shape->addOffset( start_positive, origin, ADD_BACK );
			shape->addOffset( start_negative, origin, ADD_FRONT );
			
			start_positive = GenerateRandomSurfaceOffset( start_positive,1.0 );
			start_negative = GenerateRandomSurfaceOffset( start_negative, -1.0 );
			
			
			shape->addOffset( start_positive, origin, ADD_BACK );
			shape->addOffset( start_negative, origin, ADD_FRONT );
			
			// aggiungo dei punti per essere utilizzati dal controllo collisione come punti di "giunzione" tra back e front
			shape->addOffset( start_link, origin, ADD_FRONT );
			shape->addOffset( end_link, origin, ADD_BACK );
		}

		do {
			// rimuovo i punti di giunzione per poter aggiungere i successivi punti generati
			start_link = shape->PopOffset( ADD_FRONT );
			end_link = shape->PopOffset( ADD_BACK );
			
			generated_relative_points = shape->getOffsetPoints();
			last_absolute_positive = GetNormalizedPoint( generated_relative_points.back() );
			last_absolute_negative = GetNormalizedPoint( generated_relative_points.front() );

			Point2D origin_to_reach = Point2D();
			// verifico se devo generare un punto in base alla visuale del giocatore,
			// ed eventualmente da quale lato (positivo o negativo) generare un punto
			if (this->shape != NULL) {
				Vector view_bounds = Vector(2);
				Point2D
						cameraOrigin = view->GetWorldOrigin(),
						cameraEdgeLeftOrigin = cameraOrigin,
						cameraEdgeRightOrigin = cameraOrigin,
						cameraEdgeCenterOrigin = cameraOrigin;

				unsigned int view_width = view->GetWidth();
				view_bounds.Set(BOUND_INDEX_WIDTH, view_width );

				cameraEdgeLeftOrigin = GetNormalizedPoint(cameraEdgeLeftOrigin);

				cameraEdgeRightOrigin.Add( view_bounds );
				cameraEdgeRightOrigin = GetNormalizedPoint(cameraEdgeRightOrigin);

				cameraEdgeCenterOrigin.Add(view_bounds.Scale( 0.5 ) );
				cameraEdgeCenterOrigin = GetNormalizedPoint(cameraEdgeCenterOrigin);
				
				Point2D cameraEdges[] = {
#ifndef DEBUG_LEVEL_GENERATION
						cameraEdgeLeftOrigin,
						cameraEdgeRightOrigin,
#endif
						cameraEdgeCenterOrigin

				};

				const int
#ifdef DEBUG_LEVEL_GENERATION
				n_edges = 1;
#else
				n_edges = 3;
#endif
				int i = 0;
				while (distance_required == 0 && i < n_edges ) {
					if( cameraEdges[i].GetX() <= half_width ) {
						if ( !generation_status.info_surface.isGeneratingPositiveDone ) { // il bordo si trova nell prima metà
							GetOffSet(&distance_required, last_absolute_positive, cameraEdges[i], BOUND_INDEX_WIDTH,
									  &bounds);
							if (distance_required < 0) // la camera precede l'ultimopunto
								distance_required = 0;
						}
					}
					else { // si trova nella seconda metà
						if ( !generation_status.info_surface.isGeneratingNegativeDone ) {
							GetOffSet(&distance_required, last_absolute_negative, cameraEdges[i],
									  BOUND_INDEX_WIDTH,
									  &bounds);
							if (distance_required > 0) // la camera succede l'ultimopunto
								distance_required = 0;
						}
					}
					origin_to_reach = cameraEdges[i];
					i++;
				}
			}

			if (distance_required != 0) {

				// GENERAZIONE VERTICI DEL TERRENO
				generated_relative_points = shape->getOffsetPoints();
				last_relative_positive = generated_relative_points.back(); // generation_list_positive.front();
				last_relative_negative = generated_relative_points.front(); // generation_list_negative.front();

				if (distance_required > 0) {
					old_temp = last_relative_positive;
				}
				else if (distance_required < 0) {
					old_temp = last_relative_negative;
				}
				temp = GenerateRandomSurfaceOffset(old_temp, distance_required);
				
				// verifico se i due estremi sono relativamente vicini
				VECTOR_VALUE_TYPE diff_x = 0;
				bool shouldForceLinking = shouldForceLinking = GetOffSet(&diff_x, last_absolute_negative, last_absolute_positive, BOUND_INDEX_WIDTH, &bounds );
				diff_x = abs( diff_x );
				shouldForceLinking = shouldForceLinking && diff_x <= generation_status.info_surface.distance_x.max;
				if( shouldForceLinking ){ // se sono vicini allora li collego aggiungedo 2 punti "comuni" estremi
					temp.SetY( linking_height );
					temp.SetX( half_width );
					shape->addOffset(temp, origin, ADD_BACK );
					temp.SetX( -half_width );
					shape->addOffset(temp, origin, ADD_FRONT );
					generation_status.info_surface.isGeneratingNegativeDone = true;
					generation_status.info_surface.isGeneratingPositiveDone = true;
					isPointGenerated = true;
				}
				// altrimenti controllo da quale parte generare e procedo
				else if (!generation_status.info_surface.isGeneratingPositiveDone && distance_required > 0) {
					// generation_list_positive.push_front( temp );
					if( temp.GetX() > half_width){
						temp = end_link;
						generation_status.info_surface.isGeneratingPositiveDone = true;
					}
					shape->addOffset(temp, origin, ADD_BACK );
					isPointGenerated = true;
				}
				else if (!generation_status.info_surface.isGeneratingNegativeDone && distance_required < 0) {
					if( temp.GetX() < -half_width ){
						temp = start_link;
						generation_status.info_surface.isGeneratingNegativeDone = true;
					}
					// generation_list_negative.push_front( temp );
					shape->addOffset(temp, origin, ADD_FRONT );
					isPointGenerated = true;
				}
#ifdef DEBUG_LEVEL_GENERATION
				Point2D test = temp;
				test.SetY( GetMaxHeight()-1 );
				DrawLine( view, this, temp, test, COLOR_ORANGE );
#endif
				// PROBABILITA DI GENERAZIONE ENTITA SUL PUNTO GENERATO
				if (isPointGenerated) {
					GetOffSet(&offset_x, old_temp, temp, BOUND_INDEX_WIDTH, &bounds);
					GetOffSet(&offset_y, old_temp, temp, BOUND_INDEX_HEIGHT, NULL);
					midpoint = Point2D(old_temp.GetX() + offset_x / 2.0, old_temp.GetY() + offset_y / 2.0);
					midpoint = GetNormalizedPoint( midpoint );
					TryGenerateRandomEntity(midpoint);
				}

				if( generation_status.info_surface.isGeneratingNegativeDone && generation_status.info_surface.isGeneratingPositiveDone ){
					isGenerated = true;
				}
			}
			// continua finchè la distanza richiesta non è nulla e non è stato generato un punto
		} while (!isGenerated && distance_required != 0 && !isPointGenerated );
		
		// se non è stato generato completamente riaggiungo gli offset estremi
		// per essere utilizzati dal controllo collisione come punti di "giunzione"
		if( !isGenerated ){
			shape->addOffset( start_link, origin, ADD_FRONT );
			shape->addOffset( end_link, origin, ADD_BACK );
		}
	}
}

Point2D PlanetLevel::GenerateRandomSurfaceOffset( Point2D previous, int distance_generation ){
	Vector temp = Vector( previous.GetSize() );
	Point2D point = previous;
	const unsigned int attempt_max = 3;
	unsigned int attempt = 0;
	do {
		VECTOR_VALUE_TYPE
				offset_x = RANDOM_RANGE(
								   generation_status.info_surface.distance_x.min,
								   generation_status.info_surface.distance_x.max)
						   * (distance_generation >= 0 ? 1.0 : -1.0),
				offset_y = RANDOM_RANGE(
								   generation_status.info_surface.distance_y.min,
								   generation_status.info_surface.distance_y.max)
						   + generation_status.info_surface.bound_y.min;
		if (RANDOM_RANGE(0, 100) < 50) { // scelgo se variare l'offset del punto in positivo o in negativo
			offset_y *= -1;
		}

		point.SetX(offset_x);
		point.Add(previous);
		point.SetY(offset_y);

		// l'ordinata deve essere compresa tra min_point_height e max_point_height
		point.SetY(
				max(
						min(offset_y, generation_status.info_surface.bound_y.max),
						generation_status.info_surface.bound_y.min));
		attempt++;
	} while( attempt <= attempt_max && point.GetY() <= generation_status.info_surface.bound_y.min );
    return point;
}

void PlanetLevel::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	
}