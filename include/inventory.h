/*
 * FILNAMN:       inventory.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 				  Marcus Eriksson 	910322-1371 	Y3A
 * DATUM:         2012-11-29
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
		~Inventory();

		void add(Weapon::Type weapon_type);
		void remove(unsigned int index);
		Weapon* get_item(unsigned int index);
		unsigned int get_size() const;
	private:
		std::vector<Weapon*> inventory_list;
	};

}

#endif
