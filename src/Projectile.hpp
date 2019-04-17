#pragma once

#include "Entity.hpp"
#include "Point2D.hpp"

class Level;
class GameEngine;

class Projectile : public Entity{
    protected:
    int type; // entità che ha sparato questo proiettile
    double damage; // danno che infligge a qualsiasi entità che colpisce
    Point2D fireOrigin; // punto di partenza da cui è stato generato il proiettile
    Vector direction; // vettore che indica la direzione dell'entità

    public:
    Projectile( Level *world, Point2D origin, Vector direction, double damage );
    Point2D GetFireOrigin();
    double GetDamage();
    Vector GetDirection();
    bool Update( GameEngine *game ); // aggiorna lo stato del proiettile, come la posizione, ecc...

    /**
     * @brief funzione risposta / callback che dovrà essere chiamata quando questo proiettile ha colpito una qualche entità
     * @param collide_ent 
     * @param hitOrigin 
     */
    void Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin );
};