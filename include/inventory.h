/*
 * FILNAMN:       inventory.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-11-16
 *
 * BESKRIVNING: inventory är ett indexeringsystem för föremål som är möjliga att ta upp
 *
 */

#ifndef FEED_INVENTORY_H
#define FEED_INVENTORY_H

#include "weapon.h"
#include <vector>

namespace feed
{
	class Inventory
	{
	public:
		Inventory();

		void add(const Weapon& weapon);
		void remove(unsigned int index);
		Weapon* get_item(unsigned int index);
	private:
		std::vector<Weapon> inventory_list;
	};

}

#endif
