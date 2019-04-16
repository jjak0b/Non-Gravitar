#include "GameEngine.hpp"
#include "Player.hpp"

GameEngine::GameEngine( unsigned int screen_width, unsigned int screen_height ){
    this->time = 0.0;
    this->level = NULL;
    this->view = new ViewPort( screen_width, screen_height, Point2D(0,0) );
}

bool GameEngine::update( double time, char key_pressed, unsigned width, unsigned height ){
    this->time += time;
    this->input_key = key_pressed;
    this->view->UpdateSize( width, height );
	return false;
}

bool GameEngine::frame( double dtime ){

 	// temp		
    if( this->level == NULL ){
        this->level = new Level( this->view->GetWidth(), this->view->GetHeight(), NULL );
    }

    this->level->Update( this );
    this->view->SetWorldOrigin( Point2D( 0, 0 ) );
	this->view->Clear();
    this->level->Draw( this->view );
    this->view->Refresh();
#ifdef DEBUG
	std::cout << "View Width: " << this->view->GetWidth() << std::endl;
	std::cout << "View Height: " << this->view->GetHeight() << std::endl;
	std::cout << "Pressed: " << this->GetkeyPressed()<<std::endl;
	std::cout << "Player at (" << this->level->GetPlayer()->GetOrigin().GetX() << ", " << this->level->GetPlayer()->GetOrigin().GetY() << ")" <<std::endl;
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