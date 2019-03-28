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
}

bool GameEngine::frame( double dtime ){
    this->view->Refresh();
    return false;
    if( this->level == NULL ){
        this->level = new Level( 2+this->view->GetWidth(), this->view->GetHeight(), NULL );
    }
    // temp
    this->level->Update( this );
    this->view->SetWorldOrigin( this->level->GetPlayer()->GetOrigin() );
    this->level->Draw( this->view );

    this->view->Refresh();
    // TODO
    return false;
}

char GameEngine::GetkeyPressed(){
    return this->input_key;
}

double GameEngine::GetTime(){
    return this->time;
}