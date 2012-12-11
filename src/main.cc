/*
 * FILNAMN:       main.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Mattias Fransson
 *                Herman Ekwall
 *                Joel Davidsson
 *                Marcus Eriksson
 * DATUM:         2012-12-12
 */
#include <iostream>
#include <stdexcept>
#include "game.h"

int main(int, char**)
{
    try
    {
        feed::Game game;
        game.run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
