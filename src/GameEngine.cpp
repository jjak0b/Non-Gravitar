#include "GameEngine.hpp"
#include "Player.hpp"
#include <cstring>

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
	// TODO: da implementare logica di scambio di currentLevel e currentLevel->world
	// cioè quando il giocatore passa dal sistema solare al pianeta
 	
    // temp
    if( this->currentLevel == NULL ){
        this->currentLevel = new Level( this->currentSolarSystem, this->view->GetWidth(), this->view->GetHeight(), "Level", NULL );
    }
    // if( this->currentSolarSystem == NULL ){
    //    this->currentSolarSystem = new SolarSystem( this->view->GetWidth(), this->view->GetHeight(), 4, NULL );
    //    this->currentLevel = this->currentSolarSystem;
    // }
    update_result = EntityUpdateSelector( this, this->currentLevel );
    if( !update_result ){
        Player *player = this->currentLevel->GetOutPlayer();
        if( !IsDefined( player ) ){ // il giocatore è garbage, quindi lo elimino
            player = this->currentSolarSystem->GetOutPlayer();
            player->Delete();
            delete player;
            keepPlaying = false;
        }
        else{// il giocatore è definito e il mondo non dovrebbe essere più aggiornato, quindi esce dal mondo
            // il livello di gioco ora diventa quello del sistema solare
            this->currentLevel = this->currentSolarSystem;
            if( !IsDefined( this->currentLevel ) ){ // TODO: quando ogni bunker è stato distrutto, opure ogni pianeta il livello dovrà essere flaggato come garbage
                // TODO: eliminare il pianeta dal sistema solare
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