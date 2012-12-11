/*
 * FILNAMN:       effect.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson
 * DATUM:         2012-12-12
 *
 */

#include "effect.h"
#include "messagequeue.h"

namespace feed
{
    Effect::Effect(glm::vec2 position,
                   glm::vec2 size,
                   glm::vec2 velocity,
                   SDL_Surface* image,
                   unsigned int nof_animations,
                   unsigned int nof_frames)
        : Object(position, size, velocity, image)
    {
        image_->setAnimated(nof_animations, nof_frames, true);
    }

    void Effect::update(float delta_time)
    {
        if (image_->isDone())
            MessageQueue::instance().pushMessage({MessageQueue::Message::EFFECT_DEAD, 0, this});

        Object::update(delta_time);
    }
}
