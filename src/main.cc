#include <iostream>
#include <SDL/SDL.h>
//#include <glm/glm.hpp>

#include "messagequeue.h"
#include "interactableobject.h"
#include "util.h"

using namespace feed;

int main(int, char**)
{
    // MessageQueue queue;

    // queue.pushMessage({MessageQueue::Message::FIRE, 9});
    // queue.pushMessage({MessageQueue::Message::ADD_HEALTH, 79});
    // queue.pushMessage({MessageQueue::Message::ADD_ARMOR, 100});

    // SDL_Surface* image;
    // image = SDL_LoadBMP("../data/hello.bmp");

    // MessageQueue::Message msg;
    // while (queue.pullMessage(msg))
    // {
    //     switch (msg.type)
    //     {
    //         case MessageQueue::Message::FIRE:
    //             std::cout << "You fired a " << msg.value << "mm bullet!" << std::endl;
    //             break;

    //         case MessageQueue::Message::ADD_HEALTH:
    //             std::cout << "You were healed for " << msg.value << " hp!" << std::endl;
    //             break;

    //         case MessageQueue::Message::ADD_ARMOR:
    //             std::cout << "Your armor increased by " << msg.value << " armor!" << std::endl;
    //             break;

    //         default:
    //             std::cout << "uhoh" << std::endl;
    //             break;
    //     }
    // }

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("FEED", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(685, 610, 32, SDL_SWSURFACE);
    SDL_Surface* duke = util::loadImage("data/duke.bmp");
    SDL_Surface* cat = util::loadImage("data/cat.bmp");
    SDL_Surface* alpha = util::loadImage("data/text.png");

    util::blitSurface(duke, screen, 0, 0);
    util::blitSurface(cat, screen, 100, 100);
    util::blitSurface(alpha, screen, 120, 120);

    SDL_Flip(screen);
    SDL_Delay(2000);

    SDL_FreeSurface(cat);
    SDL_FreeSurface(duke);
    SDL_FreeSurface(screen);
    SDL_Quit();

    return 0;
}
