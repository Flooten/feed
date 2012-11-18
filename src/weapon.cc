/*
 * FILNAMN:       weapon.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-11-16
 *
 */

#include "weapon.h"

namespace feed
{
	Weapon::Weapon(int type, int rate_of_fire, int last_fired, int max_clip, int max_ammo, int damage, SDL_Surface* image)
		: type_(type)
        , rate_of_fire_(rate_of_fire)
		, last_fired_(last_fired)
		, max_clip_(max_clip)
		, max_ammo_(max_ammo)
		, damage_(damage)
		, image_(image)
	{}

	SDL_Surface* Weapon::get_image()
	{
		return image_;
	}
    
    void Weapon::add_ammo(int value)
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

    void Weapon::fire()
    {
    	if (clip_ !=0)
    	{
    		--clip_;
    		// message queue
    	}
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
}
