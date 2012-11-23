/*
 * FILNAMN:       enemy.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-18
 *
 * BESKRIVNING: Denna klass definierar en fiende. Ärver från Character
 *
 */

#ifndef FEED_ENEMY_H
#define FEED_ENEMY_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "character.h"
#include "weapon.h"

namespace feed
{
    class Enemy : public Character
    {
    public:
        Enemy(const glm::vec2& position,
              const glm::vec2& size,
              const glm::vec2& velocity,
              SDL_Surface* image,
              int hitpoints,
              int armor,
              int max_health,
              int max_armor,
              Weapon& weapon);

        void fire();

    private:
        Weapon weapon_;
    };
}

#endif
