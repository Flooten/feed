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
#include "ai.h"

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

        // om ingen spelare definierats i banfilen, ladda default/krasha
        //if (player_ == nullptr)

        std::cout << "Number of enemies: " << enemy_list_.size() << std::endl;
        std::cout << "Number of envobjs: " << envobject_list_.size() << std::endl;
        std::cout << "Number of intobjs: " << intobject_list_.size() << std::endl;

        envobject_list_.push_back(new EnvironmentObject(glm::vec2(200,250), glm::vec2(50,50), glm::vec2(50,0), Resources::instance()["sq"], glm::vec2(200,200), glm::vec2(200,400)));

        //envobject_list_.back()->set_boundary_start(glm::vec2(400,200));
        //envobject_list_.back()->set_boundary_end(glm::vec2(400,400));

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

        for (auto envobject : envobject_list_)
            envobject->draw(screen, player_->get_position());

		for (auto projectile : projectile_list_)
            projectile->draw(screen, player_->get_position());

        for (auto envobject : envobject_list_)
            envobject->draw(screen, player_->get_position());

        for (auto intobject : intobject_list_)
            intobject->draw(screen, player_->get_position());

        for (auto enemy : enemy_list_)
            enemy->draw(screen, player_->get_position());

		if (player_ != nullptr)
            player_->draw(screen, player_->get_position());

        for (auto effect : effect_list_)
            effect->draw(screen, player_->get_position());
    }

    void World::update(float delta_time)
    {
        if (player_ != nullptr)
            player_->update(delta_time);

        for (auto effect : effect_list_)
            effect->update(delta_time); 

        for (auto projectile : projectile_list_)
            projectile->update(delta_time);

        for (auto enemy : enemy_list_)
            enemy->update(delta_time);

        for (auto envobject : envobject_list_)
            envobject->update(delta_time);

        for (auto envobject : envobject_list_)
        {
            handleCollision(player_, envobject);
            for (auto enemy : enemy_list_)
            {
                handleCollision(enemy, envobject);
                if (!(onScreen(enemy, player_)))
                    enemy->set_seen_player(false);

                if (enemy->get_seen_player())
                    enemy->set_seen_player((lineOfSight(enemy, player_, envobject)));
            }
        }

        for (auto it = intobject_list_.begin(); it != intobject_list_.end(); ++it)
        {
            if (isIntersecting(player_, *it))
            {
                (*it)->eventFunction();
                delete *it;
                intobject_list_.erase(it);
                break;
            }
        }

        for (auto enemy : enemy_list_)
        {
            if (enemy->get_seen_player())
            {
                enemy->set_aim(player_->get_position() - enemy->get_position());
                enemy->fire();
            }

            if (enemy->get_position().x < player_->get_position().x)
                 enemy->setAnimation(Enemy::STATIONARY_RIGHT);
            else
                enemy->setAnimation(Enemy::STATIONARY_LEFT);
        }

        for (std::size_t it = 0; it < projectile_list_.size(); ++it)
        {
            bool found = false;
            Projectile* current = projectile_list_[it];

            if (isIntersecting(current, player_))
            {
                player_->addHealth(-current->get_damage());
                MessageQueue::instance().pushMessage({MessageQueue::Message::PROJECTILE_DEAD, it, current});
                break;
            }

            for (auto envobject : envobject_list_)
            {
                if (isIntersecting(current, envobject))
                {
                    MessageQueue::instance().pushMessage({MessageQueue::Message::PROJECTILE_DEAD, it, current});
                    found = true;
                    break;
                }
            }

            if (found)
                break;

            for (auto enemy : enemy_list_)
            {
                if (isIntersecting(current, enemy))
                {
                    enemy->addHealth(-current->get_damage());
                    MessageQueue::instance().pushMessage({MessageQueue::Message::PROJECTILE_DEAD, it, current});
                    found = true;
                    break;
                }
            }
        }
    }

    void World::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
            {
                player_->fire();
                break;
            }

            case SDL_MOUSEMOTION:
            {
                // Origo
                glm::vec2 position = playerOrigin();

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
                int mouse_position_x;
                int mouse_position_y;

                SDL_GetMouseState(&mouse_position_x, &mouse_position_y);

                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        MessageQueue::instance().pushMessage({MessageQueue::Message::PAUSE_GAME});
                        break;

                    case SDLK_SPACE:
                    {
                        glm::vec2 vel = player_->get_velocity();
                        vel.y = -180.0f;
                        player_->set_velocity(vel);
                        break;
                    }

                    case SDLK_h:
                        std::cout << "Player health: " << player_->get_health() << std::endl;
                        break;

                    case SDLK_d:
                    {
                        if (mouse_position_x < playerOrigin().x)
                            // Moonwalk
                            player_->setAnimation(Player::WALKING_LEFT);
                        else
                            player_->setAnimation(Player::WALKING_RIGHT);

                        float vel_y = player_->get_velocity().y;
                        player_->set_velocity(glm::vec2(160, vel_y));
                        break;
                    }

                    case SDLK_a:
                    {
                        if (mouse_position_x >= playerOrigin().x)
                            // Moonwalk
                            player_->setAnimation(Player::WALKING_RIGHT);
                        else
                            player_->setAnimation(Player::WALKING_LEFT);

                        float vel_y = player_->get_velocity().y;
                        player_->set_velocity(glm::vec2(-160, vel_y));
                        break;
                    }

                    default:
                        break;
                }
                break;
            }

            case SDL_KEYUP:
            {
                int mouse_position_x;
                int mouse_posttion_y;

                SDL_GetMouseState(&mouse_position_x, &mouse_posttion_y);
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
                            if (mouse_position_x >= playerOrigin().x)
                                player_->setAnimation(Player::STATIONARY_RIGHT);
                            else
                                player_->setAnimation(Player::STATIONARY_LEFT);

                            float vel_y = player_->get_velocity().y;
                            player_->set_velocity(glm::vec2(0, vel_y));
                        }
                        break;

                    case SDLK_a:
                        if (!keystate[SDLK_d])
                        {
                            if (mouse_position_x < playerOrigin().x)
                                player_->setAnimation(Player::STATIONARY_LEFT);
                            else
                                player_->setAnimation(Player::STATIONARY_RIGHT);

                            float vel_y = player_->get_velocity().y;
                            player_->set_velocity(glm::vec2(0, vel_y));
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
            case MessageQueue::Message::FIRE:
            {
                Projectile* projectile = nullptr;
                Character* shooter = dynamic_cast<Character*>(msg.sender);

                switch (msg.value)
                {
                    case Weapon::PISTOL:
                    case Weapon::ENEMY_PISTOL:
                        projectile = Projectile::createPistolProjectile(shooter);
                        projectile->setAnimated(2, 6);
                        break;
                }

                if (shooter->getFacing() == 0)
                    projectile->setDirection(Projectile::RIGHT);
                else
                    projectile->setDirection(Projectile::LEFT);

                projectile_list_.push_back(projectile);

                break;
            }

            case MessageQueue::Message::PROJECTILE_DEAD:
            {
                std::cout << "Projectile " << msg.sender << " is dead" << std::endl;
                delete msg.sender;
                projectile_list_.erase(projectile_list_.begin() + msg.value);
                break;
            }

            case MessageQueue::Message::ENEMY_DEAD:
            {
                std::cout << "Enemy " << msg.sender << " is dead" << std::endl;

                for (auto it = enemy_list_.begin(); it != enemy_list_.end(); ++it)
                {
                    if (*it == msg.sender)
                    {
                        // Spawna blod
                        spawnBlood(msg.sender->get_center());
                        delete msg.sender;
                        enemy_list_.erase(it);
                        break;
                    }
                }
            }

            case MessageQueue::Message::EFFECT_DEAD:
            {
                for (auto it = effect_list_.begin(); it != effect_list_.end(); ++it)
                {
                    if (*it == msg.sender)
                    {
                        delete msg.sender;
                        effect_list_.erase(it);
                        break;
                    }
                }
            }

            case MessageQueue::Message::ADD_HEALTH:
            {
                player_->addHealth(msg.value);
                break;
            }

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
        glm::vec2 velocity;
        int health;
        int armor;

        ss >> position.x >> position.y
           >> velocity.x >> velocity.y
           >> health >> armor;

        player_ = new Player(position,
                             glm::vec2(30, 110),
                             velocity,
                             Resources::instance()["legs"],
                             health,
                             armor,
                             util::PLAYER_MAX_HEALTH,
                             util::PLAYER_MAX_ARMOR);
        player_->setAnimated(4, 8);
        player_->setTopImage(Resources::instance()["player-torso"], 2, 37);
	    player_->addWeapon(Weapon::PISTOL);
        player_->set_collision_offset(glm::vec2(50, 20));
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

    glm::vec2 World::playerOrigin()
    {
        glm::vec2 position;

        if (player_ != nullptr)
            position = glm::vec2(util::PLAYER_OFFSET_X + player_->get_size().x / 2,
                                 util::PLAYER_OFFSET_Y + player_->get_size().y / 2);

        return position;
    }

    void World::spawnBlood(const glm::vec2& position)
    {
        for (int i = 0; i < 5; ++i)
        {
            effect_list_.push_back(new Effect(position + glm::vec2(i * 5, i * 5),
                                              glm::vec2(64, 64),
                                              glm::vec2(0, 0),
                                              Resources::instance().getImage("blood"),
                                              1, 6)); 
        }
    }
}
