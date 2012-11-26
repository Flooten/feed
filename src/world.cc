/*
 * FILNAMN:       world.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-21
 *
 */

#include "world.h"
#include "util.h"
#include "audio.h"
#include "resources.h"
#include "healthcontainer.h"
#include "armorcontainer.h"
#include "weaponcontainer.h"
#include "checkpoint.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

namespace feed
{
    World::World()
    {
        std::cout << "World " << this << " online" << std::endl;
        //player_ = new Player(glm::vec2(500, 250), glm::vec2(64, 64), glm::vec2(0, 0), Resources::instance().getImage("player"), 100, 100, 100, 100, 4, 8);
        //envobject_list_.push_back(new EnvironmentObject(glm::vec2(600, 250), glm::vec2(128, 128), glm::vec2(0, 0), Resources::instance().getImage("fire"), 1, 6));
        //envobject_list_.push_back(new EnvironmentObject(glm::vec2(200, 250), glm::vec2(128, 128), glm::vec2(0, 0), Resources::instance().getImage("fireball"), 1, 6));
        //projectile_list_.push_back(new Projectile(glm::vec2(200, 250), glm::vec2(128, 128), glm::vec2(0.1, 0), Resources::instance().getImage("fireball"), 20, 1, 6));
    }

    World::World(const std::string& filename)
    {
        std::cout << "Loading world " << filename << std::endl;
        player_ = new Player(glm::vec2(350, 250), glm::vec2(64, 64), glm::vec2(0, 0), Resources::instance().getImage("legs"), 100, 100, 100, 100);
        player_->setAnimated(4, 8);
        player_->setTorsoSheet(Resources::instance().getImage("torso"), 2, 25);

        envobject_list_.push_back(new EnvironmentObject(glm::vec2(600, 250), glm::vec2(128, 128), glm::vec2(0, 0), Resources::instance().getImage("fire")));
        envobject_list_.back()->setAnimated(1, 6);

        //projectile_list_.push_back(new Projectile(glm::vec2(200, 340), glm::vec2(128, 128), glm::vec2(1, 0), Resources::instance().getImage("fireball"), 20));
        //projectile_list_.back()->setAnimated(1, 6);

        enum
        {
            IMAGES,
            AUDIO,
            ENVIRONMENT_OBJECT,
            INTERACTABLE_OBJECT
        };

        std::ifstream is(filename.c_str());

        if (!is.is_open())
            throw std::runtime_error("Failed to load worldfile");

        std::string line;
        int category;

        while(is.good())
        {
            std::getline(is, line, '\n');

            if (line.empty())
                continue;

            if (line.compare(0, 2, "//") == 0)
                continue;

            if (line == "[images]")
            {
                category = IMAGES;
                continue;
            }

            if (line == "[audio]")
            {
                category = AUDIO;
                continue;
            }

            if (line == "[environment_object]")
            {
                category = ENVIRONMENT_OBJECT;
                continue;
            }

            if (line == "[interactable_object]")
            {
                category = INTERACTABLE_OBJECT;
                continue;
            }

            switch (category)
            {
                case IMAGES:
                    loadImage(line);
                    break;

                case AUDIO:
                    loadAudio(line);
                    break;

                case ENVIRONMENT_OBJECT:
                    loadEnvironmentObject(line);
                    break;

                case INTERACTABLE_OBJECT:
                    loadInteractableObject(line);
                    break;

                default:
                    break;
            }
        }
    }

    World::~World()
    {
        std::cout << "World " << this << " dead" << std::endl;

        delete player_;

        for (auto e : projectile_list_)
            delete e;

        for (auto e : enemy_list_)
            delete e;

        for (auto e : envobject_list_)
            delete e;

        for (auto e : intobject_list_)
            delete e;
    }

    void World::draw(SDL_Surface* screen)
    {
        // Rensa screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        if (player_ != nullptr)
            player_->draw(screen, glm::vec2(0,0));//player_->get_position() - glm::vec2(screen->w * 0.382, screen->h * 0.618));

        for (auto projectile : projectile_list_)
            projectile->draw(screen, glm::vec2(0,0));//player_->get_position());

        for (auto enemy : enemy_list_)
            enemy->draw(screen, glm::vec2(0,0));//player_->get_position());

        for (auto envobject : envobject_list_)
            envobject->draw(screen, glm::vec2(0,0));//player_->get_position());

        for (auto intobject : intobject_list_)
            intobject->draw(screen, glm::vec2(0,0));//player_->get_position());
    }

    void World::update(Uint32 delta_time)
    {
        for (auto projectile : projectile_list_)
            projectile->update(delta_time);

        for (auto enemy : enemy_list_)
            enemy->update(delta_time);

        for (auto envobject : envobject_list_)
            envobject->update(delta_time);

        for (auto intobject : intobject_list_)
            intobject->update(delta_time);

        if (player_ != nullptr)
            player_->update(delta_time);
    }

    void World::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_MOUSEMOTION:
            {
                // Origo
                glm::vec2 position = player_->get_position();
                position.x += player_->get_size().x / 2;
                position.y += player_->get_size().y / 2;

                glm::vec2 aim_vec(event.motion.x - position.x, event.motion.y - position.y);

                glm::vec2 player_aim = player_->get_aim();

                float player_velocity_x = player_->get_velocity().x;

                if ((aim_vec.x < 0) && (player_aim.x >= 0))
                {
                    // Höger till vänster
                    // Hämta spelarens hastighet i x-led

                    if (player_velocity_x == 0)
                        player_->setAnimation(Player::STATIONARY_LEFT);
                    else
                        player_->setAnimation(Player::WALKING_LEFT);
                }
                else if ((aim_vec.x >= 0) && (player_aim.x < 0))
                {   
                    // Vänster till höger

                    if (player_velocity_x == 0)
                        player_->setAnimation(Player::STATIONARY_RIGHT);
                    else
                        player_->setAnimation(Player::WALKING_RIGHT);
                }

                player_->set_aim(aim_vec);
                break;
            }

            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        MessageQueue::instance().pushMessage({MessageQueue::Message::PAUSE_GAME});
                        break;

                    case SDLK_UP:
                        break;

                    case SDLK_DOWN:
                        break;

                    case SDLK_RIGHT:
                        player_->set_velocity(glm::vec2(0.3, 0));
                        player_->setAnimation(Player::WALKING_RIGHT);
                        break;

                    case SDLK_LEFT:
                        player_->set_velocity(glm::vec2(-0.3, 0));
                        player_->setAnimation(Player::WALKING_LEFT);
                        break;

                    default:
                        break;
                }
                break;
            }

            case SDL_KEYUP:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        break;

                    case SDLK_DOWN:
                        break;

                    case SDLK_RIGHT:
                        player_->set_velocity(glm::vec2(0, 0));
                        player_->setAnimation(Player::STATIONARY_RIGHT);
                        break;

                    case SDLK_LEFT:
                        player_->set_velocity(glm::vec2(0, 0));
                        player_->setAnimation(Player::STATIONARY_LEFT);
                        break;

                    default:
                        break;
                }
                
                break;
            }

            default:
                break;
        }   
    }

    void World::handleMessage(const MessageQueue::Message& msg)
    {
        switch (msg.type)
        {
            default:
                break;
        }
    }

    /*
     * Private
     */

    void World::loadImage(const std::string& str)
    {
        // std::string::size_type find = str.find(" ");

        // std::string key = str.substr(0, find);
        // std::string filename = str.substr(find + 1);

        std::stringstream ss(str);
        std::string key;
        std::string filename;

        ss >> key >> filename;

        if (!Resources::instance().addImage(key, filename))
            return;
    }

    void World::loadAudio(const std::string& str)
    {
        std::stringstream ss(str);
        std::string type;
        std::string key;
        std::string filename;

        ss >> type >> key >> filename;

        if (type == "sfx")
            Audio::instance().addSoundFx(key, filename);
        else if (type == "music")
            Audio::instance().addMusic(key, filename);
    }

    void World::loadProjectile(const std::string& str)
    {

    }

    void World::loadEnemy(const std::string& str)
    {

    }

    void World::loadEnvironmentObject(const std::string& str)
    {
        std::stringstream ss(str);

        glm::vec2 pos;
        glm::vec2 size;
        glm::vec2 vel;
        std::string image;

        ss >> pos.x >> pos.y
           >> size.x >> size.y
           >> vel.x >> vel.y
           >> image;

        envobject_list_.push_back(new EnvironmentObject(pos, size, vel, Resources::instance()[image]));
    }

    void World::loadInteractableObject(const std::string& str)
    {
        std::stringstream ss(str);

        std::string type;
        std::string image;
        glm::vec2 pos;
        glm::vec2 size;
        int val;

        ss >> type
           >> pos.x >> pos.y
           >> size.x >> size.y
           >> val
           >> image;

        if (type == "health")
            intobject_list_.push_back(new HealthContainer(pos, size, Resources::instance()[image], val));
        else if (type == "armor")
            intobject_list_.push_back(new ArmorContainer(pos, size, Resources::instance()[image], val));
        else if (type == "weapon")
            intobject_list_.push_back(new WeaponContainer(pos, size, Resources::instance()[image], val));
        else if (type == "checkpoint")
            intobject_list_.push_back(new Checkpoint(pos, size, Resources::instance()[image]));
    }
}
