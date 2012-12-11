/*
 * FILNAMN:       projectile.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson
 * DATUM:         2012-12-12
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
        bool get_boss_projectile() const;

        void set_boss_projectile(bool val);

        void setDirection(Direction direction);

        static Projectile* createPistolProjectile(Character* shooter);
        static Projectile* createShotgunProjectile(Character* shooter);

    private:
        int damage_;  // Överflödig?
        bool boss_projectile_ = false;
    };
}

#endif
