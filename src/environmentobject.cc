/*
 * FILNAMN:       environmentobject.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson   910322-1371     Y3A
 * DATUM:         2012-11-16
 *
 */

#include "environmentobject.h"
#include "util.h"
#include "messagequeue.h"

#include <iostream>

namespace feed
{
    EnvironmentObject::EnvironmentObject(const glm::vec2& position,
                                         const glm::vec2& size,
                                         const glm::vec2& velocity,
                                         int hitpoints,
                                         int max_health_,
                                         SDL_Surface* image)
        : Object(position, size, velocity, image)
        , hitpoints_(hitpoints)
        , max_health_(max_health_)
    {
    }

     EnvironmentObject::EnvironmentObject(const glm::vec2& position,
                                         const glm::vec2& size,
                                         const glm::vec2& velocity,
                                         int hitpoints,
                                         int max_health_,
                                         SDL_Surface* image,
                                         glm::vec2 boundary_start,
                                         glm::vec2 boundary_end)
        : Object(position, size, velocity, image)
        , hitpoints_(hitpoints)
        , max_health_(max_health_)
        , boundary_start_(boundary_start)
        , boundary_end_(boundary_end)
    {
        if(boundary_end != glm::vec2(0,0))
            velocity_ = glm::length(velocity)*glm::normalize(boundary_end - boundary_start);
    }

    /*
     *  Public
     */

    void EnvironmentObject::update(float delta_time)
    {   
        if (boundary_end_ != glm::vec2(0,0))
        {   
            glm::vec2 direction_ = glm::normalize(boundary_end_ - boundary_start_);

            if ((position_.x >= boundary_end_.x && position_.y <= boundary_end_.y && direction_.y <= 0) ||
                (position_.x >= boundary_end_.x && position_.y >= boundary_end_.y && direction_.y >= 0))
                velocity_ = - glm::length(velocity_)*direction_;
                    

            else if ((position_.x <= boundary_start_.x && position_.y >= boundary_start_.y && direction_.y <= 0) ||
                     (position_.x <= boundary_start_.x && position_.y <= boundary_start_.y && direction_.y >= 0))
                    velocity_ = glm::length(velocity_)*direction_;
                    
        }

        Object::update(delta_time);
    }

    void EnvironmentObject::addHealth(int value)
    {
        if (max_health_ != -1)
            {
                if (hitpoints_ + value > max_health_)
                    hitpoints_ = max_health_;
                else if (hitpoints_ + value <= 0)
                    isDestroyed();
                else
                    hitpoints_ += value;
            } 
    }

    void EnvironmentObject::isDestroyed()
    {
        MessageQueue::instance().pushMessage({MessageQueue::Message::ENVOBJECT_DEAD, 0, this});
    }

}
