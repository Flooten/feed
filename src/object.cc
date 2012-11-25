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
#include <iostream>

namespace feed
{
    Object::Object(const glm::vec2& position,
                   const glm::vec2& size,
                   const glm::vec2& velocity,
                   SDL_Surface* image)
        : position_(position)
        , size_(size)
        , velocity_(velocity)
    {
        image_ = new AnimatedImage(image);
    }

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

    // Aktiverar animering
    void Object::setAnimated(unsigned int nof_animations, unsigned int nof_frames)
    {
        image_->setAnimated(nof_animations, nof_frames);
    }

    void Object::setTorsoSheet(SDL_Surface* sheet, unsigned int nof_animations, unsigned int nof_frames)
    {
        image_->addTorsoSheet(sheet, nof_animations, nof_frames);
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
        if (image_ != nullptr)
            image_->draw(screen, position_ - offset);
    }

    void Object::update(unsigned int time)
    {
        position_.x += velocity_.x * time;
        position_.y += velocity_.y * time;

        if (image_ != nullptr)
            image_->update(time);
    }
}
