/*
 * FILNAMN:       projectile.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson 910322-1371 Y3A
 * DATUM:         2012-11-18
 *
 */

#include "projectile.h"
#include "util.h"

namespace feed
{
    Projectile::Projectile(const glm::vec2& position,
                           const glm::vec2& size,
                           const glm::vec2& velocity,
                           SDL_Surface* image,
                           int damage)
        : Object(position, size, velocity, image)
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
            util::blitSurface(image_, screen, position_.x, position_.y);
        }
    }

    void Projectile::update(unsigned int time)
    {
        position_.x += velocity_.x * time;
        position_.y += velocity_.y * time;
    }
}
