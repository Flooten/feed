/*
 * FILNAMN:       character.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 * DATUM:         2012-11-29
 *
 * BESKRIVNING: Character definerar en karaktär. Förälder till Player, Enemy och Boss. Abstrakt klass.
 *
 */

#ifndef FEED_CHARACTER_H
#define FEED_CHARACTER_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "object.h"

#include <vector>

namespace feed
{
    class Character : public Object
    {
    public:
        Character(const glm::vec2& position,
                  const glm::vec2& size,
                  const glm::vec2& velocity,
                  SDL_Surface* image,
                  int hitpoints,
                  int armor,
                  int max_health,
                  int max_armor);

        enum Animation
        {
            STATIONARY_RIGHT,
            STATIONARY_LEFT,
            WALKING_RIGHT,
            WALKING_LEFT
        };  

        void set_aim(glm::vec2 aim);
        glm::vec2 get_aim() const;
        int get_health() const;
        int getFacing() const;

        void addHealth(int value);
        void addArmor(int value);
        virtual void fire() = 0;
        void setAnimation(Animation animation);

        virtual void update(float delta_time);

        void jump();
        void set_jumping(bool state);
        bool isJumping() const;

    protected:
        virtual void isDead() = 0;

        int hitpoints_;
        int armor_;
        int max_health_;
        int max_armor_;
        bool is_jumping_ = false;

    private:
        Animation animation_;
        glm::vec2 aim_;
    };
}

#endif
