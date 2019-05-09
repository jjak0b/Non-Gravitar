#include "GameEngine.hpp"
#include <cstring>
#include "Player.hpp"
#include "SolarSystem.hpp"
#include "PlanetEntity.hpp"
#include "PlanetLevel.hpp"
#include "Projectile.hpp"

GameEngine::GameEngine( unsigned int screen_width, unsigned int screen_height ){
    this->time = 0.0;
    this->currentLevel = NULL;
    this->view = new ViewPort( screen_width, screen_height, Point2D(0,0) );
}

bool GameEngine::update( double time, char key_pressed, unsigned width, unsigned height ){
    this->time += time;
    this->input_key = key_pressed;
    this->view->UpdateSize( width, height );
	return false;
}

bool GameEngine::frame( double dtime ){

	bool keepPlaying = true;
    bool update_result = false;

    Level *last_loaded_level = this->GetCurrentLevel();
    Player *player = NULL;
	
	do{
		if( last_loaded_level != NULL ){
			if( last_loaded_level->IsGarbage() && this->GetCurrentLevel() == NULL ){ // caso in cui abbandonia totalmente il livello e non ci interressa ritornarci
				player = last_loaded_level->GetOutPlayer();
				this->UnloadLevel( last_loaded_level );
				last_loaded_level = NULL;
			}
			else{
				player = last_loaded_level->GetPlayer();
			}
		}

		// se la partita è appena iniziata oppure se il player ha cambiato sistema solare viene istanziato un nuovo sistema solare come livello
		if( this->GetCurrentLevel() == NULL){
			this->SetCurrentLevel( new SolarSystem( this->view->GetWidth(), this->view->GetHeight(), 4 ) );

			// logica di spawn o trasferimento giocatore da un sistema solare ad un altro
			Point2D spawn_point = Point2D( this->GetCurrentLevel()->GetMaxWidth()/2.0, this->GetCurrentLevel()->GetMaxHeight()/2.0 );
			if( player == NULL ){ // generiamo il giocatore e viene aggiunto al livello in automatico
				player = new Player( this->GetCurrentLevel(), spawn_point, 150.0 );
			}
			else{ // il giocatore già definito entra nel livello
				this->GetCurrentLevel()->AddEntity( player );
			}
		}

		last_loaded_level = this->GetCurrentLevel();
		// Le entità del livello si aggiornano
		update_result = EntityUpdateSelector( this, this->GetCurrentLevel() );
		// a questo punto il livello attuale potrebbe essere diverso

		if( this->GetCurrentLevel() != NULL ){
			player = this->GetCurrentLevel()->GetPlayer();
		}

		keepPlaying = IsDefined( player );

	// nel caso questa condizione si verifichi, in questo frame viene generato un nuovo livello quando ricomicomincia il ciclo
	}while( keepPlaying && this->GetCurrentLevel() == NULL );
	
    // TEMP finchè i test non sono ultimati
    this->view->SetWorldOrigin( Point2D( 0, 0 ) );
    // this->view->SetWorldOrigin( Point2D( this->currentLevel->GetPlayer()->GetOrigin().GetX() - (this->view->GetWidth()/2), 0 ) );
	this->view->Clear();
    EntityDrawSelector( this->view, last_loaded_level );
    this->view->Refresh();
#ifdef DEBUG
	std::cout << "View Width: " << this->view->GetWidth() << std::endl;
	std::cout << "View Height: " << this->view->GetHeight() << std::endl;
	std::cout << "Pressed: " << this->GetkeyPressed()<<std::endl;
	std::cout << "Player at (" << last_loaded_level->GetPlayer()->GetOrigin().GetX() << ", " << last_loaded_level->GetPlayer()->GetOrigin().GetY() << ")" <<std::endl;
#endif

	if( !keepPlaying ){ // GameOver -> Libero le risorse occuppate
		this->UnloadLevel( last_loaded_level );

		if( player != NULL ){
			player->Delete();
			delete player;
			player = NULL;
		}

		if( this->view != NULL ){
			this->view->Dispose();
			delete this->view;
			this->view = NULL;
		}
	}
    return keepPlaying;
}

char GameEngine::GetkeyPressed(){
    return this->input_key;
}

double GameEngine::GetTime(){
    return this->time;
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
		this->GetCurrentLevel()->Delete( false );
		delete this->GetCurrentLevel();
		this->SetCurrentLevel( NULL );
	}

	if( last_loaded_level != NULL ){
		last_loaded_level->Delete( false );
		delete last_loaded_level;
		last_loaded_level = NULL;
	}
}

bool IsDefined( Entity *entity ){
	return entity != NULL && !entity->IsGarbage();
}

bool EntityUpdateSelector( GameEngine *game, Entity *entity ){
	bool update_result = false;
	if( IsDefined( entity ) ){
		if( !strcmp( entity->GetClassname(), "Player" ) ){
			Player *ent = (Player*)entity;
			update_result = ent->Update( game );
		}
		else if( !strcmp( entity->GetClassname(), "Level" ) ){
			Level *ent = (Level*)entity;
			update_result = ent->Update( game );
		}
		else if( !strcmp( entity->GetClassname(), "PlanetEntity" ) ){
			PlanetEntity *ent = (PlanetEntity*)entity;
			update_result = ent->Update( game );
		}
		else if( !strcmp( entity->GetClassname(), "PlanetLevel" ) ){
			PlanetLevel *ent = (PlanetLevel*)entity;
			update_result = ent->Update( game );
		}
		else if( !strcmp( entity->GetClassname(), "SolarSystem" ) ){
			SolarSystem *ent = (SolarSystem*)entity;
			update_result = ent->Update( game );
		}
		else if( !strcmp( entity->GetClassname(), "Projectile" ) ){
			Projectile *ent = (Projectile*)entity;
			update_result = ent->Update( game );
		}
		// TODO: aggiungere altri tipi di Update
		else{
			update_result = entity->Update( game );
		}
	}
	
	return update_result;
}

void EntityDrawSelector( ViewPort *view, Entity *entity ){
	if( IsDefined( entity ) ){
		if( !strcmp( entity->GetClassname(), "Player" ) ){
			Player *ent = (Player*)entity;
			ent->Draw( view );
		}
		else if( !strcmp( entity->GetClassname(), "Level" ) ){
			Level *ent = (Level*)entity;
			ent->Draw( view );
		}
		else if( !strcmp( entity->GetClassname(), "PlanetEntity" ) ){
			PlanetEntity *ent = (PlanetEntity*)entity;
			ent->Draw( view );
		}
		else if( !strcmp( entity->GetClassname(), "PlanetLevel" ) ){
			PlanetLevel *ent = (PlanetLevel*)entity;
			ent->Draw( view );
		}
		else if( !strcmp( entity->GetClassname(), "SolarSystem" ) ){
			SolarSystem *ent = (SolarSystem*)entity;
			ent->Draw( view );
		}
		else if( !strcmp( entity->GetClassname(), "Projectile" ) ){
			Projectile *ent = (Projectile*)entity;
			ent->Draw( view );
		}
		// TODO: aggiungere altri tipi di Draw
		else{
			entity->Draw( view );
		}
	}
}
