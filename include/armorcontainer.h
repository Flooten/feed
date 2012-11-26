/*
 * FILNAMN:       armorcontainer.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-11-16
 *
 * BESKRIVNING: När spelaren interagerar med detta objekt kommer hans armor att fyllas
 *              på med ett förutbestämt värde
 *
 */

#ifndef FEED_ARMOR_CONTAINER_H
#define FEED_ARMOR_CONTAINER_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "interactableobject.h"

namespace feed
{
    class ArmorContainer : public InteractableObject
    {
    public:
        ArmorContainer(const glm::vec2& position,
                       const glm::vec2& size,
                       SDL_Surface* image,
                       int armor_value);

        virtual void eventFunction() override final;
    private:
    	int armor_value_;
    };
}

 #endif
