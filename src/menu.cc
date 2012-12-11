/*
 * FILNAMN:       menu.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson
 * DATUM:         2012-12-12
 *
 */

#include "menu.h"
#include "button.h"
#include "util.h"

namespace feed
{
    /*
     *  Public
     */

    Menu::Menu(SDL_Surface* background, const glm::vec2& position)
        : background_(background)
        , position_(position)
    {}

    Menu::~Menu() noexcept
    {
        // Avallokera
        for (auto button : button_list_)
            delete button;
    }

    void Menu::addButton(Button* button)
    {
        // Lägg till knappen och beräkna dess utritningsposition
        button_list_.push_back(button);
        button->set_position(calculateButtonPosition(button_list_.size() - 1));
    }

    void Menu::removeButton(unsigned int index)
    {
        button_list_.erase(button_list_.begin() + index);
    }

    void Menu::handleMouseMotionEvent(const SDL_MouseMotionEvent& event) const
    {
        // Låt knapparna hantera eventet
        for (auto button : button_list_)
        {
            button->handleMouseMotionEvent(event);
        }
    }

    void Menu::handleMouseButtonEvent(const SDL_MouseButtonEvent& event) const
    {
        // Låt knapparna hantera eventet
        for (auto button : button_list_)
        {
            button->handleMouseButtonEvent(event);
        }
    }

    void Menu::draw(SDL_Surface* screen)
    {
        if (background_ != nullptr)
        {
            // Rita bakgrunden
            util::blitSurface(background_, screen, position_.x, position_.y);

            // Rita alla knappar
            for (auto button : button_list_)
            {
                button->draw(screen);
            }
        }
    }

    /* 
     *  Private
     */

    glm::vec2 Menu::calculateButtonPosition(unsigned int index) const
    {
        glm::vec2 position;

        position.x = position_.x + X_OFFSET;
        position.y = position_.y + Y_OFFSET + (Button::HEIGHT + Y_SPACING) * index;

        return position;
    }
}
