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
#include "resources.h"
#include "util.h"
#include "pausemenu.h"

#include <SDL/SDL_image.h>

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
        loadWorldList();
        loadMenu();
    }

    Game::~Game()
    {
        while (!game_state_.empty())
        {
            delete game_state_.top();
            game_state_.pop();
        }

        Audio::instance().clear();
        Resources::instance().clear();
        SDL_Quit();
    }

    void Game::run()
    {
        Uint32 delta_time = 0;
        Uint32 current = 0;
        Uint32 previous = 0;

        SDL_Event event;
        MessageQueue::Message msg;

        while (running_)
        {
            current = SDL_GetTicks();
            delta_time = current - previous;
            previous = current;

            while (SDL_PollEvent(&event))
                handleSDLEvent(event);

            while (MessageQueue::instance().pullMessage(msg))
                handleMessage(msg);

            // AI
            // Kollision

            game_state_.top()->update(delta_time);
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

        // Sätt fönstrets ikon
        SDL_Surface* icon = IMG_Load("data/gfx/icon.png");
        Uint32 colorkey = SDL_MapRGB(icon->format, 255, 255, 255);
        SDL_SetColorKey(icon, SDL_SRCCOLORKEY, colorkey);
        SDL_WM_SetIcon(icon, nullptr);

        // Hämta skärmen
        screen_ = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

        Audio::instance().init();
        SDL_FreeSurface(icon);
    }

    void Game::loadResources()
    {
        Resources::instance().addImage("screen_bg", "data/piratesandfaggots.jpg");
        Resources::instance().addImage("menu_bg", "data/duke.bmp");
        Resources::instance().addImage("player", "data/gfx/player.png");

        // Menybilder
        Resources::instance().addImage("menu_background", "data/gfx/menu_background.png");
        Resources::instance().addImage("button_new_game", "data/gfx/button_new_game.png");
        Resources::instance().addImage("button_resume_game", "data/gfx/button_resume_game.png");
        Resources::instance().addImage("button_exit_to_main_menu", "data/gfx/button_exit_to_main_menu.png");
        Resources::instance().addImage("button_load_game", "data/gfx/button_load_game.png");
        Resources::instance().addImage("button_quit_game", "data/gfx/button_quit_game.png");
        Resources::instance().addImage("button_credits", "data/gfx/button_credits.png");

        Audio::instance().addSoundFx("fire", "data/high.wav");
        Audio::instance().addMusic("menu_music", "data/sound/feed01.ogg");
    }

    void Game::loadWorldList()
    {
        world_list_.push_back("data/worlds/level1.fpq");
        world_list_.push_back("data/worlds/level2.fpq");
    }

    void Game::loadMenu()
    {
        util::blitSurface(Resources::instance()["screen_bg"], screen_, 0, 0);

        game_state_.push(new MainMenu(Resources::instance().getImage("menu_background"),
                                      glm::vec2((SCREEN_WIDTH / 2) - (Resources::instance()["menu_background"]->w / 2),
                                                (SCREEN_HEIGHT / 2) - (Resources::instance()["menu_background"]->h / 2))));

        Audio::instance().playMusic("menu_music");
    }

    void Game::loadWorld()
    {
        if (current_world_ >= world_list_.size())
            return;

        game_state_.push(new World(world_list_[current_world_]));
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
                Audio::instance().toggleMusic();
                current_world_ = 0;
                loadWorld();
                break;

            case MessageQueue::Message::QUIT_GAME:
                running_ = false;
                break;

            case MessageQueue::Message::PAUSE_GAME:
                game_state_.push(new PauseMenu(Resources::instance()["menu_background"],
                                               glm::vec2((SCREEN_WIDTH / 2) - (Resources::instance()["menu_background"]->w / 2),
                                                         (SCREEN_HEIGHT / 2) - (Resources::instance()["menu_background"]->h / 2))));
                break;

            case MessageQueue::Message::RESUME_GAME:
                delete game_state_.top();
                game_state_.pop();
                break;

            case MessageQueue::Message::EXIT_TO_MAIN_MENU:
                if (game_state_.size() == 3)
                {
                    for (unsigned int i = 0; i < 2; ++i)
                    {
                        delete game_state_.top();
                        game_state_.pop();
                    }
                }                
                break;

            case MessageQueue::Message::FIRE:
                Audio::instance().playSoundFx("fire");
                break;

            default:
                game_state_.top()->handleMessage(msg);
                break;
        }
    }
}
