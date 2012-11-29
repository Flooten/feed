/*
 * FILNAMN:       projectile.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson 910322-1371 Y3A
 * DATUM:         2012-11-18
 *
 * BESKRIVNING: En projektil skapas när ett vapen avfyras.
 *              Vid interaktion med omgivningen används damage för 
 *              att avgöra hur mycket skada som tas.
 *
 */

#ifndef FEED_PROJECTILE_H
#define FEED_PROJECTILE_H

#include <glm/glm.hpp>
#include "object.h"
#include "character.h"

namespace feed
{
    class Projectile : public Object
    {
    public:
        enum Direction
        {
            RIGHT,
            LEFT
        };

        Projectile(const glm::vec2& position,
                   const glm::vec2& size,
                   const glm::vec2& velocity,
                   SDL_Surface* image,
                   int damage);

        // Getters
        int get_damage() const;

        void setDirection(Direction direction);

        static Projectile* createPistolProjectile(Character* shooter);

    private:
        int damage_;  // Överflödig?
    };
}

#endif
