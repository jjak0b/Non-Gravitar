#include "Bunker.hpp"
#include "BunkerB.hpp"
#include "Projectile.hpp"
#include "GameEngine.hpp"
#include <ctime>    
#include <cstdlib>  

    
BunkerB::BunkerB( Level *world, Point2D origin) : Bunker( world, origin, health){
}


bool BunkerB::Update(GameEngine* game) {
    
    bool update_result = this->Bunker::Update( game );
    if (health <= 0) {
        this->garbage = true;
        
    }
    if (this->counter >= 60) {

        Vector *d1 = new Vector();
        d1->Set(0,-1);
        d1->Set(1,1);
        shoot(*d1);
        
        d1->Set(0,0);
        d1->Set(1,1);
        shoot(*d1);
        
        d1->Set(0,1);
        d1->Set(1,1);
        shoot(*d1);
        
        delete d1;

        counter = 0;
    }
    
    return update_result;

}
