/*
 * FILNAMN:       interactableobject.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-16
 *
 */

#include "interactableobject.h"
#include "util.h"

namespace feed
{
    InteractableObject::InteractableObject(const glm::vec2& position,
                                           const glm::vec2& size,
                                           SDL_Surface* image)
        : Object(position, size, glm::vec2(0, 0), image)
    {}
}
