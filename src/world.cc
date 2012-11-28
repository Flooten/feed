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
#include "collision.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

namespace feed
{
    World::World()
    {
        std::cout << "World " << this << " online" << std::endl;

        envobject_list_.push_back(new EnvironmentObject(glm::vec2(450, 250), glm::vec2(128, 128), glm::vec2(0, 0), Resources::instance().getImage("fire")));
        envobject_list_.back()->setAnimated(1, 6);
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
            PLAYER,
            ENEMY
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

            if (line == "[enemy]")
            {
                category = ENEMY;
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

                case ENEMY:
                    loadEnemy(line);
                    break;

                default:
                    break;
            }
        }

        // om ingen spelare definierats i banfilen, ladda default
        if (player_ == nullptr)
            ;

        std::cout << "Number of enemies: " << enemy_list_.size() << std::endl;
        std::cout << "Number of envobjs: " << envobject_list_.size() << std::endl;
        std::cout << "Number of intobjs: " << intobject_list_.size() << std::endl;
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
		
		if (player_ != nullptr)
            player_->draw(screen, player_->get_position());
    }

    void World::update(float delta_time)
    {
        if (player_ != nullptr)
            player_->update(delta_time);

        for (auto projectile : projectile_list_)
            projectile->update(delta_time);

        for (auto enemy : enemy_list_)
            enemy->update(delta_time);

        for (auto envobject : envobject_list_)
            envobject->update(delta_time);

        // for (auto i : envobject_list_)
        //     if (collision(player_, i))
        //         std::cout << "collision" << std::endl;

        for (auto envobject : envobject_list_)
            handleCollision(player_, envobject);
    }

    void World::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_MOUSEMOTION:
            {
                // Origo
                glm::vec2 position = glm::vec2(util::PLAYER_OFFSET_X + player_->get_size().x / 2,
                                               util::PLAYER_OFFSET_Y + player_->get_size().y / 2);

                // Genererad aim-vektor
                glm::vec2 aim_vec(event.motion.x - position.x, event.motion.y - position.y);

                // Spelarens nuvarande aim-vektor
                glm::vec2 player_aim = player_->get_aim();

                // Spelarens hastighet i x-led
                float player_velocity_x = player_->get_velocity().x;

                if ((aim_vec.x < 0) && (player_aim.x >= 0))
                {
                    // Höger till vänster

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

                // Uppdatera spelares aim-vektor
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
                    {
                        glm::vec2 vel = player_->get_velocity();
                        vel.y = -30;
                        player_->set_velocity(vel);
                        break;
                    }

                    case SDLK_DOWN:
                       
                        break;

                    case SDLK_d:
                        player_->set_velocity(glm::vec2(100, 0));
                        player_->setAnimation(Player::WALKING_RIGHT);
                        break;

                    case SDLK_a:
                        player_->set_velocity(glm::vec2(-100, 0));
                        player_->setAnimation(Player::WALKING_LEFT);
                        break;

                    default:
                        break;
                }
                break;
            }

            case SDL_KEYUP:
            {
                Uint8* keystate = SDL_GetKeyState(nullptr);

                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        break;

                    case SDLK_DOWN:
                        break;

                    case SDLK_d:
                        if (!keystate[SDLK_a])
                        {
                            player_->set_velocity(glm::vec2(0, 0));
                            player_->setAnimation(Player::STATIONARY_RIGHT);
                        }
                        break;

                    case SDLK_a:
                        if (!keystate[SDLK_d])
                        {
                            player_->set_velocity(glm::vec2(0, 0));
                            player_->setAnimation(Player::STATIONARY_LEFT);
                        }
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
        std::stringstream ss(str);
        std::string key;
        std::string filename;

        ss >> key >> filename;

        // göra nått här?
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

    void World::loadProjectile(const std::string&)
    {

    }

    void World::loadEnemy(const std::string& str)
    {
        std::stringstream ss(str);
        std::string type;
        glm::vec2 position;

        ss >> type >> position.x >> position.y;

        Enemy* enemy = nullptr;

        if (type == "grunt")
            enemy = Enemy::CreateGrunt(position);
        else if (type == "heavy")
            enemy = Enemy::CreateHeavy(position);

        if (enemy != nullptr)
            enemy_list_.push_back(enemy);
    }

    void World::loadPlayer(const std::string& str)
    {
        if (player_ != nullptr)
            delete player_;

        std::stringstream ss(str);
        glm::vec2 position;
        glm::vec2 size;
        glm::vec2 velocity;
        std::string image;
        int health;
        int armor;

        ss >> position.x >> position.y
           >> velocity.x >> velocity.y
           >> health >> armor;

        //player_ = new Player(position, size, velocity, Resources::instance()[image], health, armor, max_health, max_armor);

        player_ = new Player(position,
                             glm::vec2(64, 64),
                             velocity,
                             Resources::instance()["legs"],
                             health,
                             armor,
                             max_health,
                             max_armor);
        player_->setAnimated(4, 8);
        player_->setTopImage(Resources::instance["torso"], 2, 25);
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

    bool World::line_of_sight(const Enemy* enemy, const Player* player, const EnvironmentObject* env_object)
    {
        glm::vec2 point1 = enemy->get_position();
        glm::vec2 point2 = player->get_position();
        glm::vec2 point3 = env_object->get_position();
        glm::vec2 point4 = env_object->get_position() + env_object->get_size();

        float den  = ((point4.y - point3.y) * (point2.x - point1.x) - (point4.x - point3.x) * (point2.y - point1.y));
        float num1 = ((point4.x - point3.x) * (point1.y - point3.y) - (point4.y - point3.y) * (point1.x - point3.x));
        float num2 = ((point2.x - point1.x) * (point1.y - point3.y) - (point2.y - point1.y) * (point1.x - point3.x));
        float u1 = num1/den;
        float u2 = num2/den;

        //if (den == 0 and num1 == 0 and num2 == 0)
        //    return false;
        if (den == 0)
            return true;
        else if (u1 < 0 or u1 > 1 or u2 < 0 or u2 > 1)
            return true;
        else
            return false;
    }
}
