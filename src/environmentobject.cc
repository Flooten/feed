/*
 * FILNAMN:       environmentobject.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson   910322-1371     Y3A
 * DATUM:         2012-11-16
 *
 */

#include "environmentobject.h"
#include "util.h"

#include <iostream>

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

    void EnvironmentObject::update(float delta_time)
    {
        if( velocity_.x != 0 || velocity_.y != 0)
        {
            glm::vec2 new_velocity = glm::abs(velocity_) * glm::normalize(boundary_end_ - boundary_start_);
            glm::vec2 right_corner(position_.x + size_.x, position_.y);

            if (right_corner.x > boundary_end_.x)
                velocity_ = - new_velocity;
            else if (position_.x < boundary_start_.x)
                velocity_ = new_velocity;

        }


        Object::update(delta_time);
    }
}
