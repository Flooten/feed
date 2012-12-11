/*
 * FILNAMN:       effect.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson
 * DATUM:         2012-12-12
 *
 * BESKRIVNING: Definierar effekter i spelet. Dessa är en animerad bild
 *              som spelas en gång.
 *
 */

#ifndef FEED_EFFECT_H
#define FEED_EFFECT_H

#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include "animatedimage.h"
#include "object.h"

namespace feed
{
    class Effect : public Object
    {
    public:
        Effect(glm::vec2 position,
               glm::vec2 size,
               glm::vec2 velocity,
               SDL_Surface* image,
               unsigned int nof_animations,
               unsigned int nof_frames);

        void update(float delta_time);
    };
}

#endif
