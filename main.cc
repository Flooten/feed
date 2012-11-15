#include <SDL/SDL.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    SDL_Delay(2000);
    SDL_FreeSurface(screen);
    SDL_Quit();

    return 0;
}