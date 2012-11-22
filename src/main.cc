#include <iostream>
#include "game.h"
#include "animation.h"
#include <SDL/SDL.h>
#include <glm/glm.hpp>

int main(int, char**)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Surface* screen;
	SDL_Surface* yoshi;

	yoshi = SDL_LoadBMP("data/yoshi.bmp");

	screen = SDL_SetVideoMode(1024,576,32,SDL_SWSURFACE);

	feed::Animation yoshi_test(yoshi,glm::vec2(0,0),glm::vec2(64,64),glm::vec2(0,1));

	for (unsigned int i = 0; i < 100; ++i)
	{
		yoshi_test.draw(screen,glm::vec2(12,12));
		yoshi_test.update(1);

		SDL_Delay(55);

		SDL_Flip(screen);
	}

    SDL_Quit();

    return 0;
}
