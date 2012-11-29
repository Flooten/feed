/*
 * FILNAMN:       projectile.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson 910322-1371 Y3A
 * DATUM:         2012-11-18
 *
 */

#include "projectile.h"
#include "util.h"
#include "resources.h"
#include <iostream>

namespace feed
{
    Projectile::Projectile(const glm::vec2& position,
                           const glm::vec2& size,
                           const glm::vec2& velocity,
                           SDL_Surface* image,
                           int damage)
        : Object(position, size, velocity, image)
        , damage_(damage)
    {
        setDirection(RIGHT);
    }

    int Projectile::get_damage() const
    {
        return damage_;
    }

    void Projectile::setDirection(Direction direction)
    {
        image_->setAnimation(direction);
    }

    Projectile* Projectile::createPistolProjectile(Object* sender)
    {
        glm::vec2 position;
        glm::vec2 size;
        glm::vec2 velocity;

        // Beräkna allt ovan


        return new Projectile(position, size, velocity, Resources::instance().getImage("fireball"), 5);
    }
}
