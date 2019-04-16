#pragma once

#include "Entity.hpp"
#include "Point2D.hpp"

class Level;

class Projectile : public Entity{
    protected:
    int type; // entità che ha sparato questo proiettile
    double damage; // danno che infligge a qualsiasi entità che colpisce
    Point2D fireOrigin; // punto di partenza da cui è stato generato il proiettile
    Vector direction; // vettore che indica la direzione dell'entità

    public:
    Projectile( Level *world, Point2D origin, Vector direction, double damage );
    Point2D GetTargetOrigin();
    double GetDamage();
    Vector GetDirection();
    bool Update(); // aggiorna lo stato del proiettile, come la posizione, ecc...
};