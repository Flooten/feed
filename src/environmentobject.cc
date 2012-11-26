/*
 * FILNAMN:       environmentobject.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson
 * DATUM:         2012-11-16
 *
 */

#include "environmentobject.h"
#include "util.h"

namespace feed
{
    EnvironmentObject::EnvironmentObject(const glm::vec2& position,
                                         const glm::vec2& size,
                                         const glm::vec2& velocity,
                                         SDL_Surface* image)
        : Object(position, size, velocity, image)
    {}

    /*
     *  Public
     */
    glm::vec2 EnvironmentObject::get_boundary_start() const
    {
        return boundary_start_;
    }

    glm::vec2 EnvironmentObject::get_boundary_end() const
    {
        return boundary_end_;
    }

    void EnvironmentObject::set_boundary_start(const glm::vec2& boundary_start)
    {
        boundary_start_ = boundary_start;
    }

    void EnvironmentObject::set_boundary_end(const glm::vec2& boundary_end)
    {
        boundary_end_ = boundary_end;
    }

    void EnvironmentObject::update(unsigned int time)
    {
        position_.x += velocity_.x * time;
        position_.y += velocity_.y * time;
    }
}
