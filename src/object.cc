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

namespace feed
{
    Object::Object(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity)
        : position_(position)
        , size_(size)
        , velocity_(velocity)
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
}
