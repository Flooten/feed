/*
 * FILNAMN:       weapon.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Marcus Eriksson   910322-1371     Y3A
 * DATUM:         2012-12-01
 *
 */

#include "weapon.h"
#include "resources.h"
#include "messagequeue.h"
#include <iostream>

namespace feed
{
	Weapon::Weapon(int type, int rate_of_fire, int max_clip, int max_ammo, int damage, SDL_Surface* image)
		: type_(type)
        , rate_of_fire_(rate_of_fire)
		, max_clip_(max_clip)
		, max_ammo_(max_ammo)
		, damage_(damage)
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
    	int difference = max_clip_ - clip_;

    	if (ammo_ < difference)
    		clip_ += ammo_;
    	else
    	{
    		ammo_ -= difference;
    		clip_ = max_clip_;
    	}
    }

    void Weapon::fired()
    {
    	last_fired_ = 0;
    }

    void Weapon::update(float delta_time)
    {
        last_fired_ += delta_time;
    }

    bool Weapon::isReady()
    {
        if (last_fired_ >= 1 / rate_of_fire_)
            return true;
        else
            return false;
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
    	return ammo_;
    }

    Weapon* Weapon::CreateWeapon(int type)
    {
        switch (type)
        {
            case PISTOL:
                return new Weapon(type, 3, 30, -1, 10, Resources::instance()["weapon-pistol"]);

            case SMG:
                return new Weapon(type, 10, 20, 100, 5, Resources::instance()["weapon-smg"]);

            case SHOTGUN:
                return new Weapon(type, 1, 7, 27, 5, Resources::instance()["weapon-shotgun"]);

            case ENEMY_PISTOL:
                return new Weapon(type, 1, 30, -1, 5, Resources::instance()["weapon-smg"]);

            default:
                return nullptr;
        }
    }
}
