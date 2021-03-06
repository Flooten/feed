/*
 * FILNAMN:       weapon.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Marcus Eriksson
 * DATUM:         2012-12-12
 *
 */
#include "weapon.h"
#include "resources.h"
#include "messagequeue.h"
#include "audio.h"

namespace feed
{
	Weapon::Weapon(int type, int rate_of_fire, int max_clip, int max_ammo, SDL_Surface* image)
		: type_(type)
        , rate_of_fire_(rate_of_fire)
        , clip_(max_clip)
		, max_clip_(max_clip)
		, max_ammo_(max_ammo)
		, image_(image)
	{}

	SDL_Surface* Weapon::get_image() const
	{
		return image_;
	}
    
    void Weapon::addAmmo(int value)
    {
        ammo_ += value;

        if (ammo_ > max_ammo_)
           ammo_ = max_ammo_;
    }

    void Weapon::reload()
    {
        if (max_ammo_ == -1)
        {
            clip_ = max_clip_;
            return;
        }

    	int difference = max_clip_ - clip_;

    	if (ammo_ < difference)
        {
    		clip_ += ammo_;
            ammo_ = 0;
        }
    	else
    	{
    		ammo_ -= difference;
    		clip_ = max_clip_;
    	}
    }

    void Weapon::fired()
    {
    	last_fired_ = 0;

        if (max_clip_ != -1)
            clip_ -= 1;

        switch (type_)
        {
            case PISTOL:
            case ENEMY_PISTOL:
                Audio::instance().playSoundFx("pistol-fire");
                break;

            case SHOTGUN:
                Audio::instance().playSoundFx("shotgun-fire");
                break;

            case SMG:
                Audio::instance().playSoundFx("smg-fire");
                break;

            default:
                break;
        }
    }

    void Weapon::update(float delta_time)
    {
        last_fired_ += delta_time;
    }

    bool Weapon::isReady()
    {
        if (last_fired_ >= 1 / rate_of_fire_)
        {
            if (clip_ > 0 || clip_ == -1)
                return true;
        }

        return false;
    }

    void Weapon::set_max_ammo(int max_ammo)
    {
        max_ammo_ = max_ammo;
    }

    void Weapon::set_max_clip(int max_clip)
    {
        max_clip_ = max_clip;
    }

    int Weapon::get_type() const
    {
        return type_;
    }

    int Weapon::get_clip() const
    {
    	return clip_;
    }

    int Weapon::get_ammo() const
    {
        if (max_ammo_ == -1)
            return 999;

    	return ammo_;
    }

    Weapon* Weapon::createWeapon(int type)
    {
        switch (type)
        {
            case PISTOL:
                return new Weapon(type, 3, 12, -1, Resources::instance()["weapon-pistol"]);

            case SMG:
                return new Weapon(type, 10, 20, 100, Resources::instance()["weapon-smg"]);

            case SHOTGUN:
                return new Weapon(type, 1, 7, 21, Resources::instance()["weapon-shotgun"]);

            case ENEMY_PISTOL:
                return new Weapon(type, 1, 30, -1, Resources::instance()["weapon-pistol"]);

            case BOSS_PISTOL:
                return new Weapon(type, 5, -1, -1, Resources::instance()["weapon-pistol"]);

            case BOSS_SHOTGUN:
                return new Weapon(type, 5, -1, -1, Resources::instance()["weapon-shotgun"]);

            case BOSS_SMG:
                return new Weapon(type, 15, -1, -1, Resources::instance()["weapon-smg"]);

            default:
                return nullptr;
        }
    }
}
