#include <iostream>
#include <SDL/SDL.h>
//#include <glm/glm.hpp>

#include "messagequeue.h"
#include "interactableobject.h"
#include "environmentobject.h"
#include "projectile.h"
#include "util.h"
#include "messagequeue.h"
#include "audio.h"
#include "mainmenu.h"
#include "button.h"

#include <fstream>

using namespace feed;

int main(int, char**)
{
    // Init
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("FEED", nullptr);

    // Surfaces
    SDL_Surface* screen = SDL_SetVideoMode(1024, 576, 32, SDL_SWSURFACE);
    SDL_Surface* duke = util::loadImage("data/duke.bmp");

    // Meny
    Menu menu(duke, glm::vec2((screen->w / 2) - (duke->w / 2), (screen->h / 2) - (duke->h / 2)));
    menu.addButton(new Button(util::loadImage("data/button_new_game.png"), Button::NEW_GAME));
    menu.addButton(new Button(util::loadImage("data/button_load_game.png"), Button::LOAD_GAME));
    menu.addButton(new Button(util::loadImage("data/button_exit_game.png"), Button::QUIT_GAME));

    // Meddelandekö
    MessageQueue::Message msg;

    // Eventkö
    SDL_Event event;

    bool quit = false;

    while (!quit)
    {
        // Ta hand om SDL:s eventstack
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                menu.handleMouseMotionEvent(event.motion);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    menu.handleMouseButtonEvent(event.button);
                break;

            case SDL_KEYDOWN:
                // Hantera tangenttryckning
                break;

            case SDL_QUIT:
                quit = true;
                break;

            default:
                break;
            }
        }

        // Ta hand om meddelandekön
        while (MessageQueue::instance().pullMessage(msg))
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

                case MessageQueue::Message::QUIT_GAME:
                    std::cout << "The game recieved QUIT" << std::endl;
                    quit = true;
                    break;

                case MessageQueue::Message::NEW_GAME:
                    std::cout << "The game recieved NEW_GAME" << std::endl;
                    break;

                case MessageQueue::Message::LOAD_GAME:
                    std::cout << "The game recieved LOAD_GAME" << std::endl;
                    break;

                default:
                    std::cout << "uhoh" << std::endl;
                    break;
            }
        }

        // Rita ut skärmen
        menu.draw(screen);
        SDL_Flip(screen);
        SDL_Delay(125);
    }


    

    SDL_FreeSurface(duke);
    SDL_FreeSurface(screen);
    SDL_Quit();

    return 0;

    /*if (!Audio::instance().init())
    std::cout << "Audio error" << std::endl;

    Audio::instance().addSoundFx("data/scratch.wav");
    Audio::instance().addSoundFx("data/high.wav");
    Audio::instance().addSoundFx("data/medium.wav");

    Audio::instance().playSoundFx("data/scratch.wav");
    SDL_Delay(1000);
    Audio::instance().playSoundFx("data/medium.wav");

    SDL_Delay(2000);

    Audio::instance().clear();*/

    // MessageQueue::instance().pushMessage({MessageQueue::Message::FIRE, 9});
    // MessageQueue::instance().pushMessage({MessageQueue::Message::ADD_HEALTH, 79});
    // MessageQueue::instance().pushMessage({MessageQueue::Message::ADD_ARMOR, 100});

    // SDL_Init(SDL_INIT_EVERYTHING);
    // SDL_WM_SetCaption("FEED", nullptr);

    // SDL_Surface* screen = SDL_SetVideoMode(685, 610, 32, SDL_SWSURFACE);
    // SDL_Surface* duke = util::loadImage("data/duke.bmp");

    // //EnvironmentObject* envobj = new EnvironmentObject(glm::vec2(100, 100), glm::vec2(100, 100), glm::vec2(10, 0), util::loadImage("data/cat.bmp"));
    // Projectile* projectile = new Projectile(glm::vec2(100, 100), glm::vec2(100, 100), glm::vec2(10, 0), util::loadImage("data/cat.bmp"), 100);


    // std::cout << "This projectile does " << projectile->get_damage() << " damage." << std::endl;
    // util::blitSurface(duke, screen, 0, 0);
    // projectile->draw(screen);
    // SDL_Flip(screen);

    // SDL_Delay(1000);

    // for (int i = 0; i < 20; ++i)
    // {
    //     SDL_Delay(10);
    //     projectile->update(1);
    //     util::blitSurface(duke, screen, 0, 0);
    //     projectile->draw(screen);
    //     SDL_Flip(screen);
    // }

    // SDL_Delay(2000);
}
