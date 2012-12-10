/*
 * FILNAMN:       gameworld.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-12-09
 *
 */

#include "game.h"
#include "audio.h"
#include "resources.h"
#include "util.h"
#include "pausemenu.h"
#include "wait.h"

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
        Resources::instance().init();
        SDL_FreeSurface(icon);
    }

    void Game::loadResources()
    {
        // Temp
        Resources::instance().addImage("fireball", "data/gfx/fireball.png");
        Resources::instance().addImage("dot", "data/gfx/dot.png");
        Resources::instance().addFont("optimus", "data/font.ttf", 20);

        // Levelbilder
        Resources::instance().addImage("sq", "data/gfx/sq.png");
        Resources::instance().addImage("sqd", "data/gfx/sqd.png");
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
        Resources::instance().addImage("lightning", "data/gfx/lightning.png");

        // Containerbilder
        Resources::instance().addImage("spikes", "data/gfx/spikes.png");
        Resources::instance().addImage("weapon-pistol", "data/gfx/pistol.png");
        Resources::instance().addImage("weapon-shotgun", "data/gfx/shotgun.png");
        Resources::instance().addImage("weapon-smg", "data/gfx/smg.png");
        Resources::instance().addImage("armor-container", "data/gfx/shield.png");
        Resources::instance().addImage("health-container", "data/gfx/red_cross_health.png");

        // Spelarbilder
        Resources::instance().addImage("player-torso-pistol", "data/gfx/player-torso-pistol.png");
        Resources::instance().addImage("player-torso-shotgun", "data/gfx/player-torso-shotgun.png");
        Resources::instance().addImage("player-torso-smg", "data/gfx/player-torso-smg.png");

        // Fiendebilder
        Resources::instance().addImage("grunt-torso", "data/gfx/grunt-torso.png");
        Resources::instance().addImage("heavy-torso", "data/gfx/heavy-torso.png");
        Resources::instance().addImage("firstboss", "data/gfx/first-boss.png");

        // Menybilder
        Resources::instance().addImage("menu_background", "data/gfx/menu_background.png");
        Resources::instance().addImage("button_new_game", "data/gfx/button_new_game.png");
        Resources::instance().addImage("button_resume_game", "data/gfx/button_resume_game.png");
        Resources::instance().addImage("button_exit_to_main_menu", "data/gfx/button_exit_to_main_menu.png");
        Resources::instance().addImage("button_load_game", "data/gfx/button_load_game.png");
        Resources::instance().addImage("button_quit_game", "data/gfx/button_quit_game.png");
        Resources::instance().addImage("button_credits", "data/gfx/button_credits.png");
        Resources::instance().addImage("screen_bg", "data/gfx/menu.png");

        // UI bilder
        Resources::instance().addImage("ui_meny", "data/gfx/ui.png");
        Resources::instance().addImage("armor_bar", "data/gfx/armor-bar.png");
        Resources::instance().addImage("health_bar", "data/gfx/health-bar.png");

        // Audio
        Audio::instance().addMusic("menu_music", "data/sound/feed01.ogg");
        Audio::instance().addMusic("boss_music", "data/sound/boss.ogg");
        Audio::instance().addMusic("level01", "data/sound/level01.ogg");
        Audio::instance().addMusic("elevator", "data/sound/elevator.ogg");

        // Effects
        Audio::instance().addSoundFx("click", "data/sound/click.wav");
        Audio::instance().addSoundFx("pistol-fire", "data/sound/pistol-fire.wav");
        Audio::instance().addSoundFx("pistol-reload", "data/sound/pistol-reload.wav");
        Audio::instance().addSoundFx("smg-fire", "data/sound/smg-fire.wav");
        Audio::instance().addSoundFx("smg-reload", "data/sound/smg-reload.wav");
        Audio::instance().addSoundFx("shotgun-fire", "data/sound/shotgun-fire.wav");
        Audio::instance().addSoundFx("shotgun-reload", "data/sound/shotgun-reload.wav");
        Audio::instance().addSoundFx("game-over", "data/sound/gameover.wav");
        Audio::instance().addSoundFx("checkpoint", "data/sound/checkpoint.wav");
        Audio::instance().addSoundFx("boss-death", "data/sound/enemy_death.wav");
        Audio::instance().addSoundFx("minions-attack", "data/sound/minions-attack.wav");
        Audio::instance().addSoundFx("laugh", "data/sound/laugh.wav");
        Audio::instance().addSoundFx("heed", "data/sound/heed.wav");
        Audio::instance().addSoundFx("victorious", "data/sound/victorious.wav");


    }

    void Game::loadWorldList()
    {
        world_list_.push_back("data/worlds/level1.fpq");
    }

    void Game::loadMenu()
    {
        game_state_.push(new MainMenu(Resources::instance()["menu_background"],
                                      glm::vec2((util::SCREEN_WIDTH / 2) - (Resources::instance()["menu_background"]->w / 2),
                                                (util::SCREEN_HEIGHT / 2) - (Resources::instance()["menu_background"]->h / 2))));

        Audio::instance().playMusic("menu_music");
    }

    void Game::loadWorld()
    {
        if (current_world_ >= world_list_.size())
        {
            current_world_ = 0;
            MessageQueue::instance().pushMessage({MessageQueue::Message::EXIT_TO_MAIN_MENU});
        }

        game_state_.push(new World(world_list_[current_world_]));

        // Spela nivåmusik (samma för alla världar atm)
        Audio::instance().playMusic("level01");
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
                current_world_ = 0;
                loadWorld();
                break;

            case MessageQueue::Message::CHECKPOINT:
            {
                Audio::instance().playSoundFx("checkpoint");

                if (World* ptr = dynamic_cast<World*>(game_state_.top()))
                {
                    std::ofstream out(SAVE_FILE);

                    if (!out.is_open())
                        break;

                    out << "[current_world]\n"
                        << current_world_ << "\n";

                    ptr->saveGameState(out);
                    out.close();

                    Audio::instance().playSoundFx("checkpoint");

                    // Låt world skapa en effekt
                    game_state_.top()->handleMessage(msg);
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
                std::string line;

                if (!in.is_open())
                    break;

                std::getline(in, line, '\n');

                if (line != "[current_world]")
                    break;

                std::getline(in, line, '\n');
                current_world_ = static_cast<std::size_t>(std::stoul(line));
                loadWorld();

                if (World* ptr = dynamic_cast<World*>(game_state_.top()))
                    ptr->loadGameState(in);

                in.close();

                Audio::instance().playMusic("level01");
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
                Audio::instance().resumeMusic();
                break;

            case MessageQueue::Message::EXIT_TO_MAIN_MENU:
            {
                while (game_state_.size() != 1)
                {
                    delete game_state_.top();
                    game_state_.pop();
                }

                Audio::instance().playMusic("menu_music");
                break;
            }

            case MessageQueue::Message::PLAYER_DEAD:
                Audio::instance().playSoundFx("game-over");
                Audio::instance().playMusic("menu_music");
                delete game_state_.top();
                game_state_.pop();
                break;

            case MessageQueue::Message::NEXT_WORLD:
                delete game_state_.top();
                game_state_.pop();

                // Vänta tre sekunder innan nästa värld laddas in
                game_state_.push(new Wait(screen_, 3));
                ++current_world_;
                break;

            case MessageQueue::Message::WAIT_DONE:
                delete game_state_.top();
                game_state_.pop();
                Audio::instance().playSoundFx("victorious");
                loadWorld();
                break;

            case MessageQueue::Message::CREDITS:
                std::cout << "\n" << "\n" << "\n"
                          << "                     ----------------- F.E.E.D -----------------\n"
                          << "                     |                                         |\n"
                          << "                     |              Joel Davidsson             |\n"
                          << "                     |              Herman Ekwall              |\n"
                          << "                     |              Marcus Eriksson            |\n"
                          << "                     |              Mattias Fransson           |\n"
                          << "                     |                                         |\n"
                          << "                     | LitH HT2012                             |\n"
                          << "                     -------------------------------------------\n"
                          << std::endl;
                break;

            default:
                game_state_.top()->handleMessage(msg);
                break;
        }
    }
}
