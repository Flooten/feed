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
