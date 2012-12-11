/*
 * FILNAMN:       healthcontainer.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-12-12
 *
 */

#include "healthcontainer.h"
#include "messagequeue.h"

namespace feed
{
    HealthContainer::HealthContainer(const glm::vec2& position,
                                     const glm::vec2& size,
                                     SDL_Surface* image,
                                     int health_value)
        : InteractableObject(position, size, image)
        , health_value_(health_value)
    {}
    
    void HealthContainer::eventFunction()
    {
    	MessageQueue::instance().pushMessage({MessageQueue::Message::ADD_HEALTH, health_value_, this});
    }
}
