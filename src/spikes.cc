/*
 * FILNAMN:       spikes.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Mattias Fransson
 * DATUM:         2012-12-12
 *
 */

#include "spikes.h"
#include "messagequeue.h"

namespace feed
{
    Spikes::Spikes(const glm::vec2& position,
                   const glm::vec2& size,
                   SDL_Surface* image,
                   int damage)
        : InteractableObject(position, size, image)
        , damage_(damage)
    {}

    void Spikes::eventFunction()
    {
        MessageQueue::instance().pushMessage({MessageQueue::Message::ADD_HEALTH, -damage_, 0});
    }
}
