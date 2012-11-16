/*
 * FILNAMN:       object.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-16
 *
 * BESKRIVNING: Object är den klass som alla föremål som kommer att ritas ut på skärmen ärver ifrån.
 *
 */

#ifndef FEED_OBJECT_H
#define FEED_OBJECT_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>

namespace feed
{
    class Object
    {
    public:
        Object(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity, SDL_Surface* image_);

        glm::vec2 get_position() const;
        glm::vec2 get_size() const;
        glm::vec2 get_velocity() const;

        void set_position(const glm::vec2& position);
        void set_size(const glm::vec2& size);
        void set_velocity(const glm::vec2& velocity);

        virtual void draw(SDL_Surface* screen) = 0;

        // Ej pure virual. Inte implementerad på denna nivå - bättre lösning?
        virtual void update(unsigned int){};

    protected:
        glm::vec2 position_;
        glm::vec2 size_;
        glm::vec2 velocity_;
        SDL_Surface* image_ = nullptr;  // Destrueras i gameworld
    };
}

#endif
