/*
 * FILNAMN:       environmentobject.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson   910322-1371     Y3A
 * DATUM:         2012-11-27
 *
 * BESKRIVNING: Denna klass definierar föremål som ej är fixa i bakgrunden men ej är möjliga
 *              att interagera med. Dessa objekt har möjlighet att röra sig i världen.
 *
 */

#ifndef FEED_ENVIRONMENT_OBJECT_H
#define FEED_ENVIRONMENT_OBJECT_H

#include <SDL/SDL.h>
#include <glm/glm.hpp>

#include "object.h"

namespace feed
{
    class EnvironmentObject : public Object
    {
    public:
        EnvironmentObject(const glm::vec2& position,
                          const glm::vec2& size,
                          const glm::vec2& velocity,
                          SDL_Surface* image);

        // Getters
        glm::vec2 get_boundary_start() const;
        glm::vec2 get_boundary_end() const;

        // Setters
        void set_boundary_start(const glm::vec2& boundary_start);
        void set_boundary_end(const glm::vec2& boundary_end);

    private:
        glm::vec2 boundary_start_;
        glm::vec2 boundary_end_;
    };
}

#endif
