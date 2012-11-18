/*
 * FILNAMN:       character.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-15
 *
 * BESKRIVNING: Character definerar en karaktär. Förälder till Player, Enemy och Boss. Abstrakt klass.
 *
 */

#ifndef FEED_CHARACTER_H
#define FEED_CHARACTER_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "object.h"

namespace feed
{
    class Character : public Object
    {
    public:
        Character(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity,
                  SDL_Surface* image, int hitpoints, int armor, int max_health, int max_armor);

        void set_aim(glm::vec2 aim);
        glm::vec2 get_aim() const;

        virtual void add_health(int value);
        void add_armor(int value);
        void draw(SDL_Surface* screen) override final;
        virtual void fire() = 0;

    protected:
        int hitpoints_;
        int armor_;
        int max_health_;
        int max_armor_;

    private:
        glm::vec2 aim_;
    };
}

#endif
