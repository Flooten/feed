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

    glm::vec2 Object::get_center() const
    {
        return glm::vec2(position_.x + size_.x / 2, position_.y + size_.y / 2);
    }

    // Aktiverar animering
    void Object::setAnimated(unsigned int nof_animations, unsigned int nof_frames)
    {
        image_->setAnimated(nof_animations, nof_frames);
    }

    void Object::setTopImage(SDL_Surface* sheet, unsigned int nof_animations, unsigned int nof_frames)
    {
        image_->addTopImage(sheet, nof_animations, nof_frames);
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
        glm::vec2 off = offset - glm::vec2(util::PLAYER_OFFSET_X, util::PLAYER_OFFSET_Y);

        if (image_ != nullptr)
            image_->draw(screen, position_ - off);
    }

    void Object::update(float delta_time)
    {
        position_.x += velocity_.x * delta_time;
        position_.y += velocity_.y * delta_time;

        if (image_ != nullptr)
            image_->update(delta_time);
    }
}
