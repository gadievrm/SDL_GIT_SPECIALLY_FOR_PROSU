/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

// СНАЧАЛА ИВЕНТЫ, ПОТОМ ЛОГИКА, ПОТОМ РЕНДЕР.

//Using SDL and standard IO
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include <malloc.h>

#include "Game.h"

using namespace std;

int initAllOfThisShit(){
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout <<"SDL could not initialize! SDL_Error:"<< SDL_GetError() << endl;
		return 1;
	}
	
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		cout << "Error SDL2_image Initialization"<< endl;
		return 2;
	}

	return 0;
}

int main() {
	if (initAllOfThisShit() != 0) return 1;

	Game *game = Game::init();
	if (game == NULL) {
		cout << "Could not init game!" << endl;
		return 3; 
	}
	game->start();
	while (game->run()) {}

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	return 0;
}