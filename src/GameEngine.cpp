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

	// TODO: da implementare logica di scambio di currentLevel e currentLevel->world
	// cioè quando il giocatore passa dal sistema solare al pianeta
 	// temp		
    if( this->currentLevel == NULL ){
        this->currentLevel = new Level( this->currentSolarSystem, this->view->GetWidth(), this->view->GetHeight(), "Level", NULL );
    }

    keepPlaying = this->currentLevel->Update( this );
    this->view->SetWorldOrigin( Point2D( 0, 0 ) );
	this->view->Clear();
    this->currentLevel->Draw( this->view );
    this->view->Refresh();
#ifdef DEBUG
	std::cout << "View Width: " << this->view->GetWidth() << std::endl;
	std::cout << "View Height: " << this->view->GetHeight() << std::endl;
	std::cout << "Pressed: " << this->GetkeyPressed()<<std::endl;
	std::cout << "Player at (" << this->currentLevel->GetPlayer()->GetOrigin().GetX() << ", " << this->currentLevel->GetPlayer()->GetOrigin().GetY() << ")" <<std::endl;
#endif
    // TODO
    return false;
}

char GameEngine::GetkeyPressed(){
    return this->input_key;
}

double GameEngine::GetTime(){
    return this->time;
}


bool IsDefined( Entity *entity ){
	return entity != NULL && entity->IsGarbage();
}