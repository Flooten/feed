/*
 * FILNAMN:       gameworld.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-21
 *
 */

#include "game.h"
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

    Game::Game()
    {
        initSDL();
        loadResources();
        initMenu();
        initWorld();
    }

    Game::~Game()
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

        Audio::instance().clear();
        SDL_Quit();
    }

    void Game::run()
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

            game_state_.top()->update();
            game_state_.top()->draw(screen_);

            SDL_Flip(screen_);
        }
    }

    /*
     * Private
     */

    void Game::initSDL()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_WM_SetCaption(SCREEN_CAPTION, nullptr);

        screen_ = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

        Audio::instance().init();
    }

    void Game::loadResources()
    {
        image_list_["screen_bg"] = util::loadImage("data/piratesandfaggots.jpg");
        image_list_["menu_bg"] = util::loadImage("data/duke.bmp");
    }

    void Game::initMenu()
    {
        util::blitSurface(image_list_["screen_bg"], screen_, 0, 0);

        game_state_.push(new MainMenu(image_list_["menu_bg"], glm::vec2((SCREEN_WIDTH / 2) - (image_list_["menu_bg"]->w / 2),
                                                                        (SCREEN_HEIGHT / 2) - (image_list_["menu_bg"]->h / 2))));
    }

    void Game::initWorld()
    {

    }

    void Game::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                running_ = false;
                break;

            default:
                game_state_.top()->handleSDLEvent(event);
                break;
        }
    }

    void Game::handleMessage(const MessageQueue::Message& msg)
    {
        switch (msg.type)
        {
            case MessageQueue::Message::NEW_GAME:
                game_state_.push(new World);
                break;

            case MessageQueue::Message::QUIT_GAME:
                delete game_state_.top();
                game_state_.pop();
                break;

            default:
                game_state_.top()->handleMessage(msg);
                break;
        }
    }
}
