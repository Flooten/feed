/*
 * FILNAMN:       projectile.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson 910322-1371 Y3A
 * DATUM:         2012-11-18
 *
 */

#include "projectile.h"
#include "util.h"

#include "camera.h"

namespace feed
{
    Projectile::Projectile(const glm::vec2& position,
                           const glm::vec2& size,
                           const glm::vec2& velocity,
                           SDL_Surface* image,
                           int damage,
                           unsigned int nof_animations,
                           unsigned int nof_frames)
        : Object(position, size, velocity, image, nof_animations, nof_frames)
        , damage_(damage)
    {}

    int Projectile::get_damage() const
    {
        return damage_;
    }

    void Projectile::draw(SDL_Surface* screen)
    {
        if (image_ != nullptr)
        {
            image_->draw(screen, position_ - camera);
        }
    }

    void Projectile::update(unsigned int time)
    {
        position_.x += velocity_.x * time;
        position_.y += velocity_.y * time;

        if (image_ != nullptr)
        {
            image_->update(time); 
        }
    }
}
