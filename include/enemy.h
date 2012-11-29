/*
 * FILNAMN:       enemy.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 * DATUM:         2012-11-26
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
              int weapon_type);

        enum Animation
        {
            STATIONARY_RIGHT,
            STATIONARY_LEFT,
            WALKING_RIGHT,
            WALKING_LEFT
        };

        ~Enemy();

        void fire();
        void setAnimation(Animation animation);


        static Enemy* CreateGrunt(const glm::vec2& position);
        static Enemy* CreateHeavy(const glm::vec2& position);

    private:
        Weapon* weapon_;
    };
}

#endif
