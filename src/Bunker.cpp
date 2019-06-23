#include "Bunker.hpp"
#include "DamageableEntity.hpp"
#include "Projectile.hpp"
#include "GameEngine.hpp"
#include <ctime>    
#include <cstdlib>  

Bunker::Bunker( Level *world, Point2D origin, int type ) : DamageableEntity( world, origin, NULL, "Bunker", h){
    
    this->type = type;
    
    if (type == 1) this->h = 300;
    if (type == 2) this->h = 150;
}

bool Bunker::Update(GameEngine* game) {
	
	bool update_result = this->Entity::Update( game );
    int t = game->GetTime()*100;
    this->counter++;

    
    if (this->counter >= 60) {
            
        if ( this->type == 1 ) {
            
            Vector *d1 = new Vector();
            d1->Set(0,-1);
            d1->Set(1,1);
            shoot(*d1);

            Vector *d2 = new Vector();
            d2->Set(1,1);
            shoot(*d2);

            Vector *d3 = new Vector();
            d3->Set(0,1);
            d3->Set(1,1);
            shoot(*d3);
        }

        if (this->type == 2) {

            srand(time(0));
            int r1 = random(4);
            int r2 = random (4);
            while (r1 == r2) r2 = random(4);

            Vector *d1 = new Vector();
            d1->Set(0,r1);
            d1->Set(1,1);
            shoot(*d1);

            Vector *d2 = new Vector();
            d2->Set(0,r2);
            d2->Set(1,1);
            shoot(*d2);
        }

        this->counter = 0;
    }

	return update_result;

}

Projectile *Bunker::shoot( Vector direction ){
	Point2D projectile_origin = this->GetOrigin();
	projectile_origin.Add( direction ); 
	Projectile *p = new Projectile( this->world, projectile_origin, direction, 150 );
	return p;
}


int Bunker::random(int range){
    
    int r1 = (rand() % range);
    int r2 = (rand()% range) - range;
    int r3 = (rand() % 2);

    if (r3 == 0) return r1;
    else return r2;
}