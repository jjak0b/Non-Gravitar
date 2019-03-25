#pragma once

#include "Entity.hpp"

class Projectile : public Entity{
    protected:
    Entity *owner; // entità che ha sparato questo proiettile
    double damage; // danno che infligge a qualsiasi entità che colpisce
    Point2D fireOrigin; // punto di partenza da cui è stato generato il proiettile
    Point2D targetOrigin; // punto destinazioe che dovrebbe raggiungere il proiettile

    public:
    Projectile( Level *world, Point2D fireOrigin, Point2D targetOrigin, double damage, Entity *owner );
    Point2D GetFireOrigin();
    Point2D GetTargetOrigin();
    double GetDamage();
    void update(); // aggiorna lo stato del proiettile, come la posizione, ecc...
}