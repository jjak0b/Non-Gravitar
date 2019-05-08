#include "GameEngine.hpp"
#include <cstring>
#include "Player.hpp"

GameEngine::GameEngine( unsigned int screen_width, unsigned int screen_height ){
    this->time = 0.0;
    this->currentLevel = NULL;
	this->currentSolarSystem = NULL;
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

    Level *old_level = this->currentLevel;
    Player *player = NULL;

    // se il giocatore esce da un pianeta, viene verificato se il pianeta è stato distrutto oppure
    if( this->GetCurrentSolarSystem() != NULL ){
        if( old_level != NULL && old_level->IsGarbage() ){ // quando ogni bunker è stato distrutto, ogni livello dovrà essere flaggato come garbage
            if( !strcmp( old_level->GetClassname(), "Planet" ) ){
                Planet *old_planet = (Planet*)old_level;
                player = old_planet->GetPlayer();

                old_planet->Delete();
                this->GetCurrentSolarSystem()->RemoveEntity( old_planet );
                delete old_planet;

                this->SetCurrentLevel( this->GetCurrentSolarSystem() );
            }
            else{ // eravamo nel sistema solare
                SolarSystem *old_ss = (SolarSystem*)old_level;
                player = old_ss->GetOutPlayer();

                old_ss->Delete( false );
                delete old_ss;

                this->SetCurrentSolarSystem( NULL );
                this->SetCurrentLevel( NULL );
            }
        }
    }

    // se la partita è appena iniziata, oppure se il giocatore ha cambiato sistema solare    
    if( this->GetCurrentSolarSystem() == NULL ){
        this->currentSolarSystem = new SolarSystem( this->view->GetWidth(), this->view->GetHeight(), 4, player );
        this->currentLevel = this->currentSolarSystem;
    }

    Level *last_loaded_level = this->currentLevel;
    update_result = EntityUpdateSelector( this, this->currentLevel );

    if( last_loaded_level == this->currentLevel ){ // il livello potrebbe essere cambiato quindi salto questo frame per prepararmi al prossimo
        if( !update_result ){
            Player *player = this->currentLevel->GetOutPlayer();
            if( !IsDefined( player ) ){ // il giocatore è garbage, quindi lo elimino
                player = this->currentSolarSystem->GetOutPlayer();
                player->Delete();
                delete player;
                keepPlaying = false; // GAME OVER
            }
            else{// il giocatore è definito e il mondo non dovrebbe essere più aggiornato, quindi esce dal mondo
            
            }
        }
    }
    // TEMP finchè i test non sono ultimati
    this->view->SetWorldOrigin( Point2D( 0, 0 ) );
    // this->view->SetWorldOrigin( Point2D( this->currentLevel->GetPlayer()->GetOrigin().GetX() - (this->view->GetWidth()/2), 0 ) );
	this->view->Clear();
    EntityDrawSelector( this->view, this->currentLevel );
    this->view->Refresh();
#ifdef DEBUG
	std::cout << "View Width: " << this->view->GetWidth() << std::endl;
	std::cout << "View Height: " << this->view->GetHeight() << std::endl;
	std::cout << "Pressed: " << this->GetkeyPressed()<<std::endl;
	std::cout << "Player at (" << this->currentLevel->GetPlayer()->GetOrigin().GetX() << ", " << this->currentLevel->GetPlayer()->GetOrigin().GetY() << ")" <<std::endl;
#endif

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

SolarSystem *GameEngine::GetCurrentSolarSystem(){
    return this->currentSolarSystem;
}

void GameEngine::SetCurrentSolarSystem( SolarSystem *solarsystem ){
    this->currentSolarSystem = solarsystem;
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
		else if( !strcmp( entity->GetClassname(), "Planet" ) ){
			Planet *ent = (Planet*)entity;
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
		else if( !strcmp( entity->GetClassname(), "Planet" ) ){
			Planet *ent = (Planet*)entity;
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
