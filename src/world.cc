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
    }

    World::World(const std::string& filename)
    {
        std::cout << "Loading world " << filename << std::endl;

        enum
        {
            IMAGES,
            AUDIO,
            ENVIRONMENT_OBJECT,
            INTERACTABLE_OBJECT,
            PLAYER
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

            if (line == "[player]")
            {
                category = PLAYER;
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

                case PLAYER:
                    loadPlayer(line);
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

        for (auto projectile : projectile_list_)
            projectile->draw(screen, player_->get_position());

        for (auto enemy : enemy_list_)
            enemy->draw(screen, player_->get_position());

        for (auto envobject : envobject_list_)
            envobject->draw(screen, player_->get_position());

        for (auto intobject : intobject_list_)
            intobject->draw(screen, player_->get_position());

        //player_->draw(screen, player_->get_position() - glm::vec2(screen->w / 3, screen->h / 2));
        player_->draw(screen, player_->get_position());
        //std::cout << "Dt: " << loop << " ms" << std::endl;
    }

    void World::update(float delta_time)
    {
        player_->update(delta_time);

        for (auto projectile : projectile_list_)
            projectile->update(delta_time);

        for (auto enemy : enemy_list_)
            enemy->update(delta_time);

        for (auto i : envobject_list_)
        {
            std::cout << "player: " << player_->get_position().x << " " << player_->get_position().y << std::endl;
            std::cout << "env:    " << i->get_position().x << " " << i->get_position().y << std::endl;

            if (collision(player_, i))
                std::cout << "collision" << std::endl;
        }

        // kollisionskontroll
        glm::vec2 player_pos = player_->get_position();

        if (player_pos.y > 400)
        {
            player_pos.y = 400;
            player_->set_position(player_pos);
        }

        //camera += camera_velocity * static_cast<float>(delta_time);
    }

    void World::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        MessageQueue::instance().pushMessage({MessageQueue::Message::PAUSE_GAME});
                        break;

                    case SDLK_UP:
                    {
                        glm::vec2 vel = player_->get_velocity();
                        vel.y = -100.0f;
                        player_->set_velocity(vel);
                    }
                        break;

                    case SDLK_DOWN:
                        //camera_velocity.y = 0.05f;
                        break;

                    case SDLK_RIGHT:
                        player_->set_velocity(glm::vec2(100.0f, 0.0f));
                        break;

                    case SDLK_LEFT:
                        player_->set_velocity(glm::vec2(-100.0f, 0.0f));
                        //camera_velocity.x = -0.05f;
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
                        //camera_velocity.y = 0.0f;
                        break;

                    case SDLK_DOWN:
                        //camera_velocity.y = 0.0f;
                        break;

                    case SDLK_RIGHT:
                        player_->set_velocity(glm::vec2(0.0f, 0.0f));
                        break;

                    case SDLK_LEFT:
                        player_->set_velocity(glm::vec2(0.0f, 0.0f));
                        //camera_velocity.x = -0.05f;
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
        // fiendetyper?
    }

    void World::loadPlayer(const std::string& str)
    {
        if (player_ == nullptr)
        {
            player_ = new Player(glm::vec2(512 - 70, 238 - 70),
                                 glm::vec2(140, 140),
                                 glm::vec2(0, 0),
                                 Resources::instance()["player"],
                                 100,
                                 0,
                                 100,
                                 100);
        }
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

    bool World::collision(Object* obj1, Object* obj2)
    {
        glm::vec2 diff = glm::abs((obj1->get_position() + obj1->get_size()/2.0f) - 
                                  (obj2->get_position() + obj2->get_size()/2.0f));

        if (diff.x < ((obj1->get_size().x)/2 + (obj2->get_size().x)/2) &&
            diff.y < ((obj1->get_size().y)/2 + (obj2->get_size().y)/2))
            return true;

        return 0;
    }
}
