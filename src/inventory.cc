/*
 * FILNAMN:       inventory.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 				  Marcus Eriksson 	910322-1371 	Y3A
 * DATUM:         2012-11-16
 *
 */

#include "inventory.h"
#include <iostream>

namespace feed
{
	Inventory::Inventory()
	{}

	Inventory::~Inventory()
	{
		for (auto weapon : inventory_list)
			delete weapon;
	}

	void Inventory::add(Weapon::Type weapon_type)
	{
		switch (weapon_type)
        {
            case Weapon::PISTOL:
            {
            	bool found = false;

	            for (auto weapon : inventory_list)
					if (weapon->get_type() == weapon_type)
					{
						// Lägg till ammo
						weapon->addAmmo(30);
						found = true;
					}

				if (!found)
				{
					// Lägg till vapnet
					inventory_list.push_back(Weapon::CreateWeapon(Weapon::PISTOL, 100));
				}

               break;
           	}

            default:
                break;
        }
	}

	void Inventory::remove(unsigned int index)
	{
		inventory_list.erase(inventory_list.begin() + index);
	}

	Weapon* Inventory::get_item(unsigned int index)
	{
		Weapon* weapon = nullptr;
		
		if (index < inventory_list.size())
			weapon = inventory_list[index];

		return weapon;
	}
}
