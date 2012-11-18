/*
 * FILNAMN:       checkoint.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-11-16
 *
 */

#include "checkpoint.h"
#include "messagequeue.h"

namespace feed
{
    Checkpoint::Checkpoint(const glm::vec2& position, const glm::vec2& size, SDL_Surface* image)
        : InteractableObject(position, size, image)
    {}
    
    void Checkpoint::eventFunction()
    {
    	// MessageQueue::instance().pushMessage({MessageQueue::Message::ADD_ARMOR, , this});
    }
}
