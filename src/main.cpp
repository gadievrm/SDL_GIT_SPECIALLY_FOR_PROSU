/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

// СНАЧАЛА ИВЕНТЫ, ПОТОМ ЛОГИКА, ПОТОМ РЕНДЕР.

//Using SDL and standard IO
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Game.h"

int initAllOfThisShit(){
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr <<"SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
		return 1;
	}
	
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cerr << "SDL2_image init error: "<< IMG_GetError() << std::endl;
		return 2;
	}

	Mix_Init(0);

	return 0;
}

int main(int argc, char **argv) {
	if (initAllOfThisShit() != 0) return 1;

	CGame *game = CGame::init();
	if (game == NULL) {
		std::cerr << "Could not init game!" << std::endl;
		return 3; 
	}
	game->start();
	while (game->run()) {}
	delete game;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}