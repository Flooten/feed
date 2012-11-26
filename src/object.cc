/*
 * FILNAMN:       object.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-15
 */

#include "object.h"
#include "util.h"

namespace feed
{
    Object::Object(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity, SDL_Surface* image)
        : position_(position)
        , size_(size)
        , velocity_(velocity)
        , image_(image)
    {}

    glm::vec2 Object::get_position() const
    {
        return position_;
    }

    glm::vec2 Object::get_size() const
    {
        return size_;
    }

    glm::vec2 Object::get_velocity() const
    {
        return velocity_;
    }

    void Object::set_position(const glm::vec2& position)
    {
        position_ = position;
    }

    void Object::set_size(const glm::vec2& size)
    {
        size_ = size;
    }

    void Object::set_velocity(const glm::vec2& velocity)
    {
        velocity_ = velocity;
    }

    void Object::draw(SDL_Surface* screen, const glm::vec2& offset)
    {
        glm::vec2 off = offset - glm::vec2(screen->w / 3, screen->h / 2);

        if (screen != nullptr)
            util::blitSurface(image_, size_, screen, position_ - off);
    }

    void Object::update(float delta_time)
    {
        static glm::vec2 gravity(0.0f, 50.0f);

        velocity_ += gravity * delta_time;
        position_ += velocity_ * delta_time;
    }
}
