/*
 * FILNAMN:       world.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-12-05
 *
 */

#include "world.h"
#include "util.h"
#include "audio.h"
#include "resources.h"
#include "healthcontainer.h"
#include "armorcontainer.h"
#include "weaponcontainer.h"
#include "specialcontainer.h"
#include "spikes.h"
#include "checkpoint.h"
#include "collision.h"
#include "ai.h"
#include "firstboss.h"

#include <iostream>
#include <sstream>
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

        std::cout << "Number of enemies: " << enemy_list_.size() << std::endl;
        std::cout << "Number of envobjs: " << envobject_list_.size() << std::endl;
        std::cout << "Number of intobjs: " << intobject_list_.size() << std::endl;
    }

    World::~World()
    {
        std::cout << "World " << this << " dead" << std::endl;

        delete player_;
        delete ui_;

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

        util::blitSurface(Resources::instance()["bg"], screen, 0, 0);

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

        if (boss_ != nullptr)
            boss_->draw(screen, player_->get_position());

		if (player_ != nullptr)
            player_->draw(screen, player_->get_position());

        for (auto effect : effect_list_)
            effect->draw(screen, player_->get_position());

        if (ui_ != nullptr)
            ui_->draw(screen);
    }

    void World::update(float delta_time)
    {
        if (player_ != nullptr)
            player_->update(delta_time);

        if (boss_ != nullptr)
            boss_->update(delta_time);

        for (auto effect : effect_list_)
            effect->update(delta_time); 

        for (auto projectile : projectile_list_)
            projectile->update(delta_time);

        for (auto enemy : enemy_list_)
            enemy->update(delta_time);

        for (auto envobject : envobject_list_)
            envobject->update(delta_time);

        for (auto intobject : intobject_list_)
            intobject->update(delta_time);

        for (auto envobject : envobject_list_)
        {
            handleCollision(player_, envobject);
            handleCollision(boss_, envobject);

            for (auto enemy : enemy_list_)
            {                   
                handleCollision(enemy, envobject);

                if (!(onScreen(enemy, player_)))
                    enemy->set_seen_player(false);

                // if(enemy->get_previous_seen_state() && !fieldOfVison(enemy,player_))
                //     enemy->turn();

                if(enemy->get_seen_player())
                {
                    enemy->set_seen_player(fieldOfVison(enemy, player_) && lineOfSight(enemy, player_, envobject));
                    enemy->set_previous_seen_state(true);
                }
            }
        }

        // Kolla interactable objects
        // Objekten tas bort 
        for (auto it = intobject_list_.begin(); it != intobject_list_.end(); ++it)
        {
            if (isIntersecting(player_, *it))
            {
                (*it)->eventFunction();

                // Undvik segfault genom att ta bort objektet i nästa meddelande-loop.
                // Måste vara så eftersom vi använder det *it pekar på i ADD_WEAPON
                MessageQueue::instance().pushMessage({MessageQueue::Message::INTOBJECT_DEAD,
                                                      static_cast<int>(it - intobject_list_.begin()), *it});
                break;
            }
        }

        for (auto enemy : enemy_list_)
        {
            if (enemy->get_seen_player())
            {
                enemy->set_aim(player_->get_position() - enemy->get_position());
                enemy->fire();
            
                if (enemy->get_position().x < player_->get_position().x) 
                {
                    if(enemy->isWalking())
                    {
                        enemy->walkRight();
                        enemy->stopWalking();
                    }
                    else
                     enemy->setAnimation(Enemy::STATIONARY_RIGHT);
                }
                else
                {
                    if(enemy->isWalking())
                    {
                        enemy->walkLeft();
                        enemy->stopWalking();
                    }
                    else
                     enemy->setAnimation(Enemy::STATIONARY_LEFT);
                }
            }
            else if (enemy->isHit())
            {
                enemy->turn();
                enemy->set_hit(false);
            }

            else if(!enemy->isWalking())  
                enemy->continueWalking();
        }

        for (auto it = projectile_list_.begin(); it != projectile_list_.end(); ++it)
        {
            bool found = false;

            if (isIntersecting(*it, player_))
            {
                player_->addArmor(-(*it)->get_damage());
                MessageQueue::instance().pushMessage({MessageQueue::Message::PROJECTILE_DEAD, 0, *it});
                found = true;
            }

            if (found)
                break;

            for (auto envobject : envobject_list_)
            {
                if (isIntersecting(*it, envobject))
                {
                    envobject->addHealth(-(*it)->get_damage());
                    MessageQueue::instance().pushMessage({MessageQueue::Message::PROJECTILE_DEAD, 0, *it});
                    found = true;
                    break;
                }
            }
            if (found)
                break;

            for (auto enemy : enemy_list_)
            {
                if (isIntersecting(*it, enemy))
                {
                    enemy->addArmor(-(*it)->get_damage());
                    enemy->set_hit(true);
                    MessageQueue::instance().pushMessage({MessageQueue::Message::PROJECTILE_DEAD, 0, *it});
                    found = true;
                    break;
                }
            }
            
            if(!(onScreen(*it, player_)))
                MessageQueue::instance().pushMessage({MessageQueue::Message::PROJECTILE_DEAD, 0, *it});
        }

        ui_->update();
        checkKeyState();
    }

    void World::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
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
                        if (!player_->isJumpLocked())
                            effect_list_.push_back(new Effect(player_->get_position(),
                                                              glm::vec2(128, 128),
                                                              glm::vec2(0, 0),
                                                              Resources::instance().getImage("smoke-jump"),
                                                              1, 10));
                        player_->jump();
                        break;
                    }

                    case SDLK_h:
                        std::cout << "Player health: " << player_->get_health() << std::endl;
                        break;

                    case SDLK_i:
                            player_->set_god_mode(!player_->godMode());
                            break;

                    case SDLK_s:
                    std::cout << player_->get_position().x << " " << player_->get_position().y  << " "
                              << player_->get_velocity().x << " " << player_->get_velocity().y  << " "
                              << player_->get_health() << " " << player_->get_armor() << std::endl;
                              break;

                    case SDLK_c:
                    {
                        glm::vec2 tmp = glm::vec2(mouse_position_x, mouse_position_y);
                        tmp = util::screenToWorld(tmp, player_->get_position());
                        
                        std::cout << "x: " << tmp.x << " y: " << tmp.y << std::endl;
                        break;
                    }

                    case SDLK_p:
                    {
                        glm::vec2 pos = util::screenToWorld(glm::vec2(mouse_position_x, mouse_position_y), player_->get_position());
                        glm::vec2 start = pos + glm::vec2(30, 0);
                        glm::vec2 end = pos - glm::vec2(30, 0);
                        enemy_list_.push_back(Enemy::createGrunt(pos, start, end));
                        break;
                    }

                    case SDLK_UP:
                        player_->incrementInventory();
                        break;

                    case SDLK_DOWN:
                        player_->decrementInventory();
                        break;

                    case SDLK_r:
                        player_->reload();
                        break;

                    default:
                        break;
                }
                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            {
                if (event.button.button == SDL_BUTTON_WHEELUP)
                    player_->incrementInventory();

                if (event.button.button == SDL_BUTTON_WHEELDOWN)
                    player_->decrementInventory();

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
                    case Weapon::SMG:
                        projectile = Projectile::createPistolProjectile(shooter);
                        addProjectile(projectile, shooter);
                        break;

                    case Weapon::SHOTGUN:
                    {
                        for (int i = 0; i < 5; ++i)
                        {
                            projectile = Projectile::createShotgunProjectile(shooter);
                            addProjectile(projectile, shooter);
                        }
                        break;
                    }
                }
                break;
            }

            case MessageQueue::Message::PROJECTILE_DEAD:
            {
                for (auto it = projectile_list_.begin(); it != projectile_list_.end(); ++it)
                {
                    if (*it == msg.sender)
                    {
                        delete msg.sender;
                        projectile_list_.erase(it);
                        break;
                    }
                }
                break;
            }

            case MessageQueue::Message::ENEMY_DEAD:
            {
                for (auto it = enemy_list_.begin(); it != enemy_list_.end(); ++it)
                {
                    if (*it == msg.sender)
                    {
                        // Spawna blod
                        spawnBlood(msg.sender->get_position());
                        delete msg.sender;
                        enemy_list_.erase(it);
                        Audio::instance().playSoundFx("enemy_dead");
                        break;
                    }
                }
                break;
            }

            case MessageQueue::Message::EFFECT_DEAD:
            {
                std::cout << "Effect " << msg.sender << " is dead" << std::endl;

                for (auto it = effect_list_.begin(); it != effect_list_.end(); ++it)
                {
                    if (*it == msg.sender)
                    {
                        delete msg.sender;
                        effect_list_.erase(it);
                        break;
                    }
                }
                break;
            }

            case MessageQueue::Message::ADD_HEALTH:
                player_->addHealth(msg.value);
                break;

            case MessageQueue::Message::ADD_ARMOR:
                player_->addArmor(msg.value);
                break;

            case MessageQueue::Message::ADD_WEAPON:
            {
                int ammo = 0;
                if(WeaponContainer* ptr = dynamic_cast<WeaponContainer*>(msg.sender))
                    ammo = ptr->get_ammo();
                player_->addWeapon(static_cast<Weapon::Type>(msg.value), ammo);
                break;
            }

            case MessageQueue::Message::ENVOBJECT_DEAD:
            {
                for (auto it = envobject_list_.begin(); it != envobject_list_.end(); ++it)
                {
                    if (*it == msg.sender)
                    {
                        delete msg.sender;
                        envobject_list_.erase(it);
                        break;
                    }
                }
                break;
            }

            case MessageQueue::Message::INTOBJECT_DEAD:
            {
                delete msg.sender;
                intobject_list_.erase(intobject_list_.begin() + msg.value);
                break;
            }

            case MessageQueue::Message::SPAWN_WALL:
            {
                envobject_list_.push_back(new EnvironmentObject(glm::vec2(12100, -200), glm::vec2(50, 50), glm::vec2(0, 0), 0, -1, Resources::instance()["sq"]));
                envobject_list_.push_back(new EnvironmentObject(glm::vec2(12100, -150), glm::vec2(50, 50), glm::vec2(0, 0), 0, -1, Resources::instance()["sq"]));
                envobject_list_.push_back(new EnvironmentObject(glm::vec2(12100, -100), glm::vec2(50, 50), glm::vec2(0, 0), 0, -1, Resources::instance()["sq"]));
                envobject_list_.push_back(new EnvironmentObject(glm::vec2(12100, -50), glm::vec2(50, 50), glm::vec2(0, 0), 0, -1, Resources::instance()["sq"]));

                // Spawna första bossen
                if (boss_ !=  nullptr)
                    delete boss_;

                boss_ = new FirstBoss(glm::vec2(12500, -130),
                                      glm::vec2(128, 128),
                                      glm::vec2(50, 0),
                                      Resources::instance()["firstboss"],
                                      200,
                                      300,
                                      glm::vec2(12200, 0),
                                      glm::vec2(13200, 0));

                break;
            }

            case MessageQueue::Message::SPAWN_ADDS_PHASE_TWO:
                enemy_list_.push_back(Enemy::createGrunt(glm::vec2(12350, -400)));
                enemy_list_.push_back(Enemy::createGrunt(glm::vec2(12700, -400)));
                enemy_list_.push_back(Enemy::createGrunt(glm::vec2(13050, -400)));
                break;

            case MessageQueue::Message::SPAWN_ADDS_PHASE_THREE:
                enemy_list_.push_back(Enemy::createHeavy(glm::vec2(12500, -600)));
                enemy_list_.push_back(Enemy::createHeavy(glm::vec2(12900, -600)));
                break;

            default:
                break;
        }
    }

    void World::saveGameState(std::ofstream& out)
    {
        if (!out.is_open())
            return;

        // Spara undan spelarens tillstånd
        out << "[player]\n";
        out << player_->get_position().x << " " << player_->get_position().y  << " "
            << player_->get_velocity().x << " " << player_->get_velocity().y  << " "
            << player_->get_health() << " " << player_->get_armor() << "\n";

        out << "[inventory]\n";

        out << player_->get_inventory_index() << "\n";

        unsigned int num_weapons = player_->get_inventory()->get_size();
        for (unsigned int i = 1; i < num_weapons; ++i)
        {
            std::string type;
            const Weapon* current_weapon = player_->get_inventory()->get_item(i);

            switch (current_weapon->get_type())
            {
                case Weapon::SMG:
                    type = "smg";
                    break;

                case Weapon::SHOTGUN:
                    type = "shotgun";
                    break;

                default:
                    break;
            }

            out << type << " "
                << current_weapon->get_clip() + current_weapon->get_ammo() << "\n";
        }
    }

    void World::loadGameState(std::ifstream& in)
    {
        if (!in.is_open())
            return;

        std::string line;
        std::getline(in, line, '\n');

        // Ladda in spelaren
        if (line != "[player]")
            return;

        std::getline(in, line, '\n');
        loadPlayer(line);

        std::getline(in, line, '\n');

        if (line != "[inventory]")
            return;

        unsigned int current_weapon = 0;
        in >> current_weapon;

        while (in.good())
        {
            std::string type;
            //int clip = 0;
            int ammo = 0;

            in >> type >> ammo;

            // Hårdkodade clip-size-värden här.
            // Typiskt obra...
            if (type == "smg")
                player_->addWeapon(Weapon::SMG, ammo - 20);
            else if (type == "shotgun")
                player_->addWeapon(Weapon::SHOTGUN, ammo - 7);

            std::cout << "Adding " << type << " with " << ammo << " bullets" << std::endl;
        }

        player_->set_inventory_index(current_weapon);
    }

    /*
     * Private
     */

    void World::addProjectile(Projectile* projectile, const Character* shooter)
    {
        if (projectile != nullptr)
        {
            projectile->setAnimated(2, 6);

            if (shooter->getFacing() == 0)
                projectile->setDirection(Projectile::RIGHT);
            else
                projectile->setDirection(Projectile::LEFT);

            projectile_list_.push_back(projectile);
        }
    }

    //
    // Alla inladdningsfunktioner tar en sträng (motsvarande en rad i fpq-filen)
    // och lägger in den i motsvarande resurslista.
    // Bilder som fattas är inte nödvändigtvis fel, dvs ingen åtgärd tas för bilder som
    // saknas, varken vid inladdning av bild eller ihopkoppling mellan objekt och bild.
    // Se till att kolla bilden mot nullptr innan användning i alla fall.
    //

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

    void World::loadEnemy(const std::string& str)
    {
        std::stringstream ss(str);
        std::string type;
        glm::vec2 position;
        glm::vec2 boundary_start;
        glm::vec2 boundary_end;

        ss >> type >> position.x >> position.y
           >> boundary_start.x >> boundary_start.y
           >> boundary_end.x >> boundary_end.y;

        Enemy* enemy = nullptr;

        //std::cout << "Load enemy: " << boundary_end.x << " " << boundary_end.y << std::endl;

        if (type == "grunt")
            enemy = Enemy::createGrunt(position, boundary_start, boundary_end);
        else if (type == "heavy")
            enemy = Enemy::createHeavy(position, boundary_start, boundary_end);

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
        player_->setTopImage(Resources::instance()["player-torso-pistol"], 2, 37);
	    player_->addWeapon(Weapon::PISTOL);
        player_->set_collision_offset(glm::vec2(50, 40));

        // Ui beror på spelar-pekaren, se till att de skapas tillsammans
        // annars segfaultar spelet vid LOAD_GAME
        if (ui_ != nullptr)
            delete ui_;

        ui_ = new Ui(player_,
                     Resources::instance()["ui_meny"],
                     Resources::instance()["health_bar"],
                     Resources::instance()["armor_bar"]);
    }

    void World::loadEnvironmentObject(const std::string& str)
    {
        std::stringstream ss(str);

        glm::vec2 pos;
        glm::vec2 size;
        glm::vec2 vel;
        int hit;
        int max;
        std::string image;
        glm::vec2 boundary_start;
        glm::vec2 boundary_end;

        ss >> pos.x >> pos.y
           >> size.x >> size.y
           >> vel.x >> vel.y
           >> hit >> max
           >> image
           >> boundary_start.x >> boundary_start.y
           >> boundary_end.x >> boundary_end.y;

        envobject_list_.push_back(new EnvironmentObject(pos, size, vel, hit, max, Resources::instance()[image], boundary_start, boundary_end));
    }

    void World::loadInteractableObject(const std::string& str)
    {
        std::stringstream ss(str);

        std::string type;
        std::string image;
        glm::vec2 pos;
        glm::vec2 size;
        int val = 0;

        ss >> type
           >> pos.x >> pos.y
           >> size.x >> size.y
           >> val
           >> image;

        if (type == "health")
            intobject_list_.push_back(new HealthContainer(pos, size, Resources::instance()[image], val));
        else if (type == "armor")
            intobject_list_.push_back(new ArmorContainer(pos, size, Resources::instance()[image], val));
        else if (type == "checkpoint")
            intobject_list_.push_back(new Checkpoint(pos, size, Resources::instance()[image]));
        else if (type == "spikes")
            intobject_list_.push_back(new Spikes(pos, size, Resources::instance()[image], val));
        else if (type == "fire")
        {
            intobject_list_.push_back(new Spikes(pos, size, Resources::instance()[image], val));
            intobject_list_.back()->setAnimated(1, 6);
        }
        else if (type == "shotgun")
            intobject_list_.push_back(new WeaponContainer(pos, size, Weapon::SHOTGUN, val, Resources::instance()[image]));
        else if (type == "smg")
            intobject_list_.push_back(new WeaponContainer(pos, size, Weapon::SMG, val, Resources::instance()[image]));
        else if (type == "surprise")
            intobject_list_.push_back(new SpecialContainer(pos, size, Resources::instance()[image]));        
    }

    void World::loadBoss(const std::string& str) 
    {
        std::stringstream ss(str);
        std::string type;
        std::string image;
        glm::vec2 position;
        glm::vec2 velocity;
        glm::vec2 size;
        int hitpoints;
        int armor;

        glm::vec2 boundary_start;
        glm::vec2 boundary_end;

        ss >> type >> position.x >> position.y
           >> size.x >> size.y
           >> boundary_start.x >> boundary_start.y
           >> boundary_end.x >> boundary_end.y;

        if(type == "firstboss")
        {
            boss_ = new FirstBoss(position, size, velocity, Resources::instance()["firstboss"], 50, 250);
            boss_->setAnimated(4, 8);
            boss_->setTopImage(Resources::instance()["player-torso-pistol"], 2, 37);
            boss_->addWeapon(Weapon::PISTOL);
        }
    }

    void World::checkKeyState()
    {
        int mouse_position_x;
        int mouse_posttion_y;
        Uint8 mousestate = SDL_GetMouseState(&mouse_position_x, &mouse_posttion_y);

        Uint8* keystate = SDL_GetKeyState(nullptr);

        if (mouse_position_x < playerOrigin().x)
            player_->setAnimation(Player::STATIONARY_LEFT);
        else
            player_->setAnimation(Player::STATIONARY_RIGHT);

        float vel_y = player_->get_velocity().y;
        player_->set_velocity(glm::vec2(0, vel_y));

        if (mousestate & SDL_BUTTON(1))
            player_->fire();

        if (keystate[SDLK_a])
        {
            if (mouse_position_x >= playerOrigin().x)
                player_->setAnimation(Player::WALKING_RIGHT);
            else
                player_->setAnimation(Player::WALKING_LEFT);

            float vel_y = player_->get_velocity().y;
            player_->set_velocity(glm::vec2(-160, vel_y));
        }

        if (keystate[SDLK_d])
        {
            if (mouse_position_x >= playerOrigin().x)
                player_->setAnimation(Player::WALKING_RIGHT);
            else
                player_->setAnimation(Player::WALKING_LEFT);

            float vel_y = player_->get_velocity().y;
            player_->set_velocity(glm::vec2(160, vel_y));
        }
    }

    glm::vec2 World::playerOrigin() const
    {
        glm::vec2 position;

        if (player_ != nullptr)
            position = glm::vec2(util::PLAYER_OFFSET_X +
                                 player_->get_collision_offset().x +
                                 (player_->get_size().x - player_->get_collision_offset().x) / 2,
                                 util::PLAYER_OFFSET_Y +
                                 player_->get_collision_offset().y +        
                                 (player_->get_size().y - player_->get_collision_offset().y)/ 2);

        return position;
    }

    void World::spawnBlood(const glm::vec2& position)
    {
        for (int i = 0; i < 6; ++i)
        {
            int x_rand = (rand() % 30) - 15;
            int y_rand = (rand() % 30) - 15;

            effect_list_.push_back(new Effect(position + glm::vec2(x_rand, y_rand),
                                              glm::vec2(128, 128),
                                              glm::vec2(0, 0),
                                              Resources::instance().getImage("blood"),
                                              1, 6)); 
        }
    }
}
