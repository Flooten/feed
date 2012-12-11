/*
 * FILNAMN:       checkpoint.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Marcus Eriksson
 * DATUM:         2012-12-12
 *
 */

#include "checkpoint.h"
#include "messagequeue.h"

namespace feed
{
    Checkpoint::Checkpoint(const glm::vec2& position,
                           const glm::vec2& size,
                           SDL_Surface* image)
        : InteractableObject(position, size, image)
    {}
    
    void Checkpoint::eventFunction()
    {
    	// Skicka meddelandet
        MessageQueue::instance().pushMessage({MessageQueue::Message::CHECKPOINT});
    }
}
