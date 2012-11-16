#include <iostream>
#include <SDL/SDL.h>
//#include <glm/glm.hpp>

#include "messagequeue.h"
#include "interactableobject.h"

using namespace feed;

int main(int, char**)
{
    MessageQueue queue;

    queue.pushMessage({MessageQueue::Message::FIRE, 9});
    queue.pushMessage({MessageQueue::Message::ADD_HEALTH, 79});
    queue.pushMessage({MessageQueue::Message::ADD_ARMOR, 100});

    SDL_Surface* image;
    image = SDL_LoadBMP("../data/hello.bmp");

    MessageQueue::Message msg;
    while (queue.pullMessage(msg))
    {
        switch (msg.type)
        {
            case MessageQueue::Message::FIRE:
                std::cout << "You fired a " << msg.value << "mm bullet!" << std::endl;
                break;

            case MessageQueue::Message::ADD_HEALTH:
                std::cout << "You were healed for " << msg.value << " hp!" << std::endl;
                break;

            case MessageQueue::Message::ADD_ARMOR:
                std::cout << "Your armor increased by " << msg.value << " armor!" << std::endl;
                break;

            default:
                std::cout << "uhoh" << std::endl;
                break;
        }
    }

    return 0;
}
