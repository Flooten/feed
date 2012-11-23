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

namespace feed
{
    class Projectile : public Object
    {
    public:
        Projectile(const glm::vec2& position,
                   const glm::vec2& size,
                   const glm::vec2& velocity,
                   SDL_Surface* image,
                   int damage);

        // Getters
        int get_damage() const;

        // Överskuggning
        //void draw(SDL_Surface* screen) override final;  // Möjligt med const?
        void update(unsigned int time);

    private:
        int damage_;
    };
}

#endif
