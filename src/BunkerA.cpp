#include "Bunker.hpp"
#include "BunkerA.hpp"
#include "Projectile.hpp"
#include "GameEngine.hpp"
#include <ctime>    
#include <cstdlib>  

    
BunkerA::BunkerA( Level *world, Point2D origin) : Bunker( world, origin, health){
}


bool BunkerA::Update(GameEngine* game) {
    
    bool update_result = this->Bunker::Update( game );
    
    if (health <= 0) {
        this->garbage = true;
        
    }
    if (this->counter >= 60) {

        srand(time(0));
        int r1 = random(4);
        int r2 = random (4);
        while (r1 == r2) r2 = random(4);

        Vector *d1 = new Vector();
        d1->Set(0,r1);
        d1->Set(1,1);
        shoot(*d1);

        d1->Set(0,r2);
        d1->Set(1,1);
        shoot(*d1);
 
        counter = 0;
    }
    
    return update_result;

}

