#include "gameworld.h"
#include "audio.h"
#include "util.h"

#include <iostream>
#include <utility>

namespace feed
{
    namespace
    {
        const int SCREEN_WIDTH = 1024;
        const int SCREEN_HEIGHT = 576;
        const char* SCREEN_CAPTION = "F.E.E.D.";
    }

    GameWorld::GameWorld()
    {
        initSDL();
        loadResources();
        initMenu();
        initWorld();
    }

    GameWorld::~GameWorld()
    {
        for (auto element : projectile_list_)
            delete element;

        for (auto element : enemy_list_)
            delete element;

        for (auto element : intobject_list_)
            delete element;

        for (auto element : envobject_list_)
            delete element;

        for (auto& element : image_list_)
            SDL_FreeSurface(element.second);

        delete player_;
        delete main_menu_;
        delete pause_menu_;

        Audio::instance().clear();
        SDL_Quit();
    }

    void GameWorld::run()
    {
        SDL_Event event;
        MessageQueue::Message msg;

        while (running_)
        {
            while (SDL_PollEvent(&event))
                handleSDLEvent(event);

            while (MessageQueue::instance().pullMessage(msg))
                handleMessage(msg);

            // AI
            // Kollision

            draw();
            SDL_Flip(screen_);
        }
    }

    /*
     * Private
     */

    void GameWorld::initSDL()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_WM_SetCaption(SCREEN_CAPTION, nullptr);

        screen_ = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

        Audio::instance().init();
    }

    void GameWorld::loadResources()
    {
        image_list_["screen_bg"] = util::loadImage("data/piratesandfaggots.jpg");
        image_list_["menu_bg"] = util::loadImage("data/duke.bmp");
    }

    void GameWorld::initMenu()
    {
        util::blitSurface(image_list_["screen_bg"], screen_, 0, 0);

        main_menu_ = new Menu(image_list_["menu_bg"], glm::vec2((SCREEN_WIDTH / 2) - (image_list_["menu_bg"]->w / 2),
                                                           (SCREEN_HEIGHT / 2) - (image_list_["menu_bg"]->h / 2)));
    }

    void GameWorld::initWorld()
    {

    }

    void GameWorld::draw()
    {
        // rita världen

        if (menu_on_)
            main_menu_->draw(screen_);
    }

    void GameWorld::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                running_ = false;
                break;

            default:
                break;
        }
    }

    void GameWorld::handleMessage(const MessageQueue::Message& msg)
    {
        switch (msg.type)
        {
            default:
                break;
        }
    }
}
