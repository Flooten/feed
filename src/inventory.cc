/*
 * FILNAMN:       inventory.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-11-16
 *
 */

#include "inventory.h"

namespace feed
{
	Inventory::Inventory()
	{}

	void Inventory::add(const Weapon& weapon)
	{
		bool found = 0;

		for(unsigned int i = 0; i < inventory_list.size(); i++)
		{
			if (inventory_list[i].get_type() == weapon.get_type())
			{
				inventory_list[i].addAmmo(weapon.get_ammo());
				found = 1;
			}
		}

		if (!found)
			inventory_list.push_back(weapon);
	}

	void Inventory::remove(unsigned int index)
	{
		inventory_list.erase(inventory_list.begin() + index);
	}

	Weapon* Inventory::get_item(unsigned int index)
	{
		return &(inventory_list[index]);
	}

}
