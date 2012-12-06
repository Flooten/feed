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
#include <SDL/SDL_ttf.h>

#include <iostream>
#include <utility>
#include <fstream>

namespace feed
{
    namespace
    {
        const char* SCREEN_CAPTION = "F.E.E.D.";
        const char* SAVE_FILE = "data/saves/latest_checkpoint.fpq";
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
        TTF_Quit();
        SDL_Quit();
    }

    void Game::run()
    {
        float delta_time = 0;
        Uint32 current = 0;
        Uint32 previous = 0;

        SDL_Event event;
        MessageQueue::Message msg;

        while (running_)
        {
            current = SDL_GetTicks();
            delta_time = static_cast<float>(current - previous) / 1000;
            previous = current;

            while (SDL_PollEvent(&event))
                handleSDLEvent(event);

            while (MessageQueue::instance().pullMessage(msg))
                handleMessage(msg);

            game_state_.top()->draw(screen_);
            game_state_.top()->update(delta_time);

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
        screen_ = SDL_SetVideoMode(util::SCREEN_WIDTH, util::SCREEN_HEIGHT, 32, SDL_SWSURFACE);

        Audio::instance().init();
        TTF_Init();
        SDL_FreeSurface(icon);
    }

    void Game::loadResources()
    {
        // Temp
        Resources::instance().addImage("screen_bg", "data/piratesandfaggots.jpg");
        Resources::instance().addImage("menu_bg", "data/duke.bmp");
        Resources::instance().addImage("fireball", "data/gfx/fireball.png");
        Resources::instance().addImage("dot", "data/gfx/dot.png");


        // Levelbilder
        Resources::instance().addImage("sq", "data/gfx/sq.png");
        Resources::instance().addImage("2h", "data/gfx/2h.png");
        Resources::instance().addImage("2v", "data/gfx/2v.png");
        Resources::instance().addImage("3h", "data/gfx/3h.png");
        Resources::instance().addImage("3v", "data/gfx/3v.png");
        Resources::instance().addImage("4h", "data/gfx/4h.png");
        Resources::instance().addImage("4v", "data/gfx/4v.png");
        Resources::instance().addImage("5h", "data/gfx/5h.png");
        Resources::instance().addImage("5v", "data/gfx/5v.png");
        Resources::instance().addImage("fu", "data/gfx/fire-up.png");
        Resources::instance().addImage("fd", "data/gfx/fire-down.png");
        Resources::instance().addImage("bg", "data/gfx/desert.png");

        // Common
        Resources::instance().addImage("legs", "data/gfx/legs.png");
        Resources::instance().addImage("legs-dark", "data/gfx/legs-dark.png");
        Resources::instance().addImage("blood", "data/gfx/blood.png");
        Resources::instance().addImage("smoke-jump", "data/gfx/smoke-jump.png");

        // Containerbilder
        Resources::instance().addImage("spikes", "data/gfx/spikes.png");
        Resources::instance().addImage("weapon-pistol", "data/gfx/pistol.png");
        Resources::instance().addImage("weapon-shotgun", "data/gfx/shotgun.png");
        Resources::instance().addImage("weapon-smg", "data/gfx/smg.png");
        Resources::instance().addImage("checkpoint", "data/gfx/checkpoint.jpg");

        // Spelarbilder
        Resources::instance().addImage("player-torso-pistol", "data/gfx/player-torso-pistol.png");
        Resources::instance().addImage("player-torso-shotgun", "data/gfx/player-torso-shotgun.png");
        Resources::instance().addImage("player-torso-smg", "data/gfx/player-torso-smg.png");

        // Fiendebilder
        Resources::instance().addImage("grunt-torso", "data/gfx/grunt-torso.png");
        Resources::instance().addImage("heavy-torso", "data/gfx/heavy-torso.png");

        // Menybilder
        Resources::instance().addImage("menu_background", "data/gfx/menu_background.png");
        Resources::instance().addImage("button_new_game", "data/gfx/button_new_game.png");
        Resources::instance().addImage("button_resume_game", "data/gfx/button_resume_game.png");
        Resources::instance().addImage("button_exit_to_main_menu", "data/gfx/button_exit_to_main_menu.png");
        Resources::instance().addImage("button_load_game", "data/gfx/button_load_game.png");
        Resources::instance().addImage("button_quit_game", "data/gfx/button_quit_game.png");
        Resources::instance().addImage("button_credits", "data/gfx/button_credits.png");

        // UI bilder
        Resources::instance().addImage("ui_meny", "data/gfx/ui.png");
        Resources::instance().addImage("armor_bar", "data/gfx/armor-bar.png");
        Resources::instance().addImage("health_bar", "data/gfx/health-bar.png");

        // Audio
        Audio::instance().addMusic("menu_music", "data/sound/feed01.ogg");

        // Effects
        Audio::instance().addSoundFx("click", "data/sound/click.wav");
      //  Audio::instance().addSoundFx("pistol_fire", "data/sound/mp5-1.wav");
        Audio::instance().addSoundFx("enemy_dead", "data/sound/enemy_death.wav");


    }

    void Game::loadWorldList()
    {
        //world_list_.push_back("data/worlds/level1.fpq");
        world_list_.push_back("data/worlds/level_test.fpq");
    }

    void Game::loadMenu()
    {
        game_state_.push(new MainMenu(Resources::instance().getImage("menu_background"),
                                      glm::vec2((util::SCREEN_WIDTH / 2) - (Resources::instance()["menu_background"]->w / 2),
                                                (util::SCREEN_HEIGHT / 2) - (Resources::instance()["menu_background"]->h / 2))));

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
                Audio::instance().pauseMusic();
                current_world_ = 0;
                loadWorld();
                break;

            case MessageQueue::Message::CHECKPOINT:
            {
                if (World* ptr = dynamic_cast<World*>(game_state_.top()))
                {
                    std::ofstream out(SAVE_FILE);

                    if (!out.is_open())
                        break;

                    out << "[current_world]\n"
                        << current_world_ << "\n";

                    ptr->saveGameState(out);
                    out.close();
                }
                break;
            }

            case MessageQueue::Message::LOAD_GAME:
            {
                while (game_state_.size() != 1)
                {
                    delete game_state_.top();
                    game_state_.pop();
                }

                std::ifstream in(SAVE_FILE);

                if (!in.is_open())
                    break;

                std::string line;
                in >> line;

                if (line != "[current_world]")
                    break;

                in >> current_world_;
                loadWorld();

                if (World* ptr = dynamic_cast<World*>(game_state_.top()))
                    ptr->loadGameState(in);

                in.close();

                break;
            }

            case MessageQueue::Message::QUIT_GAME:
                running_ = false;
                break;

            case MessageQueue::Message::PAUSE_GAME:
            {
                game_state_.push(new PauseMenu(screen_,
                                               Resources::instance()["menu_background"],
                                               glm::vec2((util::SCREEN_WIDTH / 2) - (Resources::instance()["menu_background"]->w / 2),
                                                         (util::SCREEN_HEIGHT / 2) - (Resources::instance()["menu_background"]->h / 2))));
                break;
            }

            case MessageQueue::Message::RESUME_GAME:
                delete game_state_.top();
                game_state_.pop();
                break;

            case MessageQueue::Message::EXIT_TO_MAIN_MENU:
            {
                while (game_state_.size() != 1)
                {
                    delete game_state_.top();
                    game_state_.pop();
                }
                break;
            }

            case MessageQueue::Message::PLAYER_DEAD:
                delete game_state_.top();
                game_state_.pop();
                break;

            default:
                game_state_.top()->handleMessage(msg);
                break;
        }
    }
}
