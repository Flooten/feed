/*
 * FILNAMN:       inventory.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-16
 *
 * BESKRIVNING: inventory är ett indexeringsystem för föremål som är möjliga att ta upp
 *
 */

#ifndef FEED_INVENTORY_H
#define FEED_INVENTORY_H

namespace feed
{
	class Inventory
	{
	public:
		Inventory();

		void add(Weapon& weapon);
		void remove(int index);
		Weapon* get_item(int index);
	private:
		std::vector<Weapon*> inventory_list;
	};

}

#endif