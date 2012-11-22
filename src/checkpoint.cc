/*
 * FILNAMN:       checkpoint.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
                  Marcus Eriksson 910322-1371 Y3A
 * DATUM:         2012-11-22
 *
 */

#include "checkpoint.h"
#include "messagequeue.h"

namespace feed
{
    Checkpoint::Checkpoint(const glm::vec2& position,
                           const glm::vec2& size,
                           SDL_Surface* image,
                           unsigned int nof_animations,
                           unsigned int nof_frames)
        : InteractableObject(position, size, image, nof_animations, nof_frames)
    {}
    
    void Checkpoint::eventFunction()
    {
    	// Skicka meddelandet
        MessageQueue::instance().pushMessage({MessageQueue::Message::CHECKPOINT});
    }
}
