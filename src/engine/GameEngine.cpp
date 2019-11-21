
#include "GameEngine.hpp"
#include "entities/Player.hpp"
#include "entities/SolarSystem.hpp"
#include "entities/PlanetEntity.hpp"
#include "entities/PlanetLevel.hpp"
#include "entities/Projectile.hpp"

#include <cstring>

GameEngine::GameEngine( unsigned int screen_width, unsigned int screen_height ){
	this->time = 0.0;
	this->deltaTime = 0.0;
	this->currentLevel = NULL;
	this->view = new ViewPort( screen_width, screen_height, Point2D(0,0) );
	this->garbage_collector = list<Entity*>();
}

bool GameEngine::update( double deltaTime, char key_pressed, unsigned width, unsigned height ){
	this->deltaTime = deltaTime;
	this->time += deltaTime;
	this->input_key = key_pressed;
	return this->view->UpdateSize( width, height );
}

bool GameEngine::frame( double dtime ){

	bool keepPlaying = true;
	bool update_result = false;

	Level *last_loaded_level = this->GetCurrentLevel();
	Player *player = NULL;
	
	do{
		if( IsDefined( last_loaded_level ) ){
			player = last_loaded_level->GetPlayer();
		}
		// se la partita è appena iniziata oppure se il player ha cambiato sistema solare viene istanziato un nuovo sistema solare come livello
		if( this->GetCurrentLevel() == NULL){
			Vector _bounds = Vector( 2 );
			_bounds.Set( BOUND_INDEX_WIDTH, this->view->GetWidth() );
			_bounds.Set( BOUND_INDEX_HEIGHT, this->view->GetHeight() );
			this->SetCurrentLevel( new SolarSystem( _bounds, RANDOM_RANGE( 1, 5 ) ) );

			// logica di spawn o trasferimento giocatore da un sistema solare ad un altro
			Point2D spawn_point = Point2D( 0, this->GetCurrentLevel()->GetMaxHeight()/2.0 );
			if( player == NULL ){ // generiamo il giocatore e viene aggiunto al livello in automatico
				player = new Player( this->GetCurrentLevel(), spawn_point, PLAYER_HEALTH );
			}
			else{ // il giocatore già definito entra nel livello
				this->GetCurrentLevel()->AddEntity( player );
				player->SetOrigin( spawn_point );
			}
		}

		last_loaded_level = this->GetCurrentLevel(); // aggiorno il livello attuale
		
		// Le entità del livello si aggiornano
		update_result = IsDefined( last_loaded_level ) && last_loaded_level->Update( this );// update_result = EntityUpdateSelector( this, last_loaded_level );
		// a questo punto il livello attuale potrebbe essere diverso

		keepPlaying = IsDefined( player );
	// nel caso questa condizione si verifichi, in questo frame viene generato un nuovo livello quando ricomicomincia il ciclo
	}while( keepPlaying && this->GetCurrentLevel() == NULL );
	
	// TEMP finchè i test non sono ultimati
	Point2D world_point_relative_to_bottom_left = Point2D( player->GetOrigin().GetX() - (this->view->GetWidth()/2.0), 0 );
	this->SetCameraWorldOrigin( world_point_relative_to_bottom_left );

	if( IsDefined( last_loaded_level ) ){
		last_loaded_level->Draw( this->view ); // EntityDrawSelector( this->view, last_loaded_level );
	}
	this->view->Refresh();
	this->view->Clear();

#ifdef DEBUG
	std::cout << "#####################################\n";
	std::cout << "View Width: " << this->view->GetWidth() << "\n";
	std::cout << "View Height: " << this->view->GetHeight() << "\n";
	std::cout << "Pressed: " << this->GetkeyPressed()<< "\n";
	if( player != NULL ){
		std::cout << "Player at (" << player->GetOrigin().GetX() << ", " << player->GetOrigin().GetY() << ")" <<std::endl;
	}
	else{
		std::cout << "Player UNDEFINED !!!!" <<std::endl;
	}
#endif

	if( !keepPlaying ){ // GameOver -> Libero le risorse occuppate
		this->UnloadLevel( last_loaded_level );
		last_loaded_level = NULL;
		
		if( player != NULL ){
			player->Delete( this );
			player = NULL;
		}

		if( this->view != NULL ){
			delete this->view;
			this->view = NULL;
		}
	}

	this->ClearGarbageCollector();

	return keepPlaying;
}

ViewPort* GameEngine::GetViewport(){
    return this->view;
}

void GameEngine::SetCameraWorldOrigin( Point2D origin ){
	if( this->view != NULL ){
		this->view->SetWorldOrigin( origin );
	}
}

Point2D GameEngine::GetCameraWorldOrigin(){
    Point2D origin;
    if( this->view != NULL ){
        origin = this->view->GetWorldOrigin();
    }
    return origin;
}
char GameEngine::GetkeyPressed(){
	return this->input_key;
}

double GameEngine::GetTime(){
	return this->time;
}

double GameEngine::GetDeltaTime(){
	return this->deltaTime;
}

Level *GameEngine::GetCurrentLevel(){
	return this->currentLevel;
}

void GameEngine::SetCurrentLevel( Level *level ){
	this->currentLevel = level;
}

void GameEngine::UnloadLevel( Level *last_loaded_level ){
	if( this->GetCurrentLevel() == last_loaded_level ){
		this->SetCurrentLevel( NULL ); // poichè è lo stesso livello, dealloco l'ultimo livello specificato
	}
	else if( this->GetCurrentLevel() != NULL ){
		this->GetCurrentLevel()->Delete( this );
		this->SetCurrentLevel( NULL );
	}

	if( last_loaded_level != NULL ){
		last_loaded_level->Delete( this );
		last_loaded_level = NULL;
	}
}

void GameEngine::AddGarbage(Entity *entity) {
    if( entity != NULL ){
        if( !entity->IsGarbage() ){
            entity->Delete( this );
        }
        this->garbage_collector.push_front( entity );
    }
}

void GameEngine::ClearGarbageCollector(){
	Entity *entity;
	while( !this->garbage_collector.empty() ){
		entity = this->garbage_collector.back();
		delete entity;
		this->garbage_collector.pop_back();
	}
}

bool IsDefined( Entity *entity ){
	return entity != NULL && !entity->IsGarbage();
}
