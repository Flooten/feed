/*
 * FILNAMN:       player.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-18
 *
 */

#include "player.h"

 namespace feed
 {
    Player::Player(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity,
                         SDL_Surface* image, int hitpoints, int armor)
                            : Character(position, size, velocity, image, hitpoints, armor)
                            {}

    void Player::addWeapon(Weapon& weapon)
    {
        inventory.add(weapon);
    }

    int Player::get_inventory_index() const
    {
        return inventory_index;
    }

    void Player::set_inventory_index(int index)
    {
        inventory_index = index;
    }

    void Player::fire()
    {
        (inventory.get_item(inventory_index))->fire();
    }
 }
