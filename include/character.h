/*
 * FILNAMN:       character.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-15
 *
 * BESKRIVNING: Object är den klass som alla föremål som kommer att ritas ut på skärmen ärver ifrån.
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
        Character(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity, const SDL_Surface* image, int hitpoints, int armor);

        void set_aim(glm::vec2 aim);
        glm::vec2 get_aim();
        void add_health(int value);
        void add_armor(int value);
        virtual void fire() = 0;

        virtual

    private:
        int hitpoints;
        int armor;
        glm::vec2 aim;
    };

}

#endif