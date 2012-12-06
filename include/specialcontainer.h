/*
 * FILNAMN:       specialcontainer.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-11-16
 *
 * BESKRIVNING: När spelaren interagerar med detta objekt kommer hans armor att fyllas
 *              på med ett förutbestämt värde
 *
 */

#ifndef FEED_SPECIAL_CONTAINER_H
#define FEED_SPECIAL_CONTAINER_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "interactableobject.h"

namespace feed
{
    class SpecialContainer : public InteractableObject
    {
    public:
        SpecialContainer(const glm::vec2& position,
                       const glm::vec2& size,
                       SDL_Surface* image);

        virtual void eventFunction() override final;
    private:
    };
}

 #endif
