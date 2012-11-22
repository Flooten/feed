/*
 * FILNAMN:       interactableobject.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-16
 *
 * BESKRIVNING: Denna klass definierar föremål som ej är fixa i bakgrunden och är möjliga
 *              att interagera med.
 *
 */

#ifndef FEED_INTERACTABLE_OBJECT_H
#define FEED_INTERACTABLE_OBJECT_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "object.h"

namespace feed
{
    class InteractableObject : public Object
    {
    public:
        InteractableObject(const glm::vec2& position,
                           const glm::vec2& size,
                           SDL_Surface* image,
                           unsigned int nof_animations,
                           unsigned int nof_frames);

        void draw(SDL_Surface* screen) override final;
        void update(unsigned int time) override final;
        virtual void eventFunction() = 0;

    private:
    };
}

 #endif
