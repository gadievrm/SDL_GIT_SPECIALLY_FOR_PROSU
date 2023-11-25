/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

// СНАЧАЛА ИВЕНТЫ, ПОТОМ ЛОГИКА, ПОТОМ РЕНДЕР.



//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include <windows.h>
#include <malloc.h>

#include "Graphics.h"
#include "Entity.h"
#include "Player.h"

using namespace std;

//Structures



//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



bool aKeyPressed = false;
bool wKeyPressed = false;
bool dKeyPressed = false;
bool sKeyPressed = false;

SDL_Renderer *renderer;

Player player;





int initAllOfThisShit(){

	SDL_Init(SDL_INIT_EVERYTHING);
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
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



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	if (initAllOfThisShit() != 0) return 1;
	
	//Create window
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL )
	{
		cout << "Window could not be created! SDL_Error:" << SDL_GetError() << endl;
		return 3;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	screenSurface = SDL_GetWindowSurface( window );
	image_t *background  = imageLoad("data//environment//Background//Back.png", renderer);
	player.setImage(imageLoad("data//sprites//player//idle//playeridle.png", renderer));
	player.setPosX(SCREEN_WIDTH/2 - player.getImage()->w / 2);
	player.setPosY(SCREEN_HEIGHT/2 - player.getImage()->h /2);
	bool quit = false;
	while(!quit){
		SDL_Event e;
		
		while( SDL_PollEvent( &e ) ){ 
			if (e.type == SDL_KEYDOWN){
				int scancode = e.key.keysym.scancode;
				if(scancode == SDL_SCANCODE_A) aKeyPressed = true;
				if(scancode == SDL_SCANCODE_W) wKeyPressed = true;
				if(scancode == SDL_SCANCODE_S) sKeyPressed = true;
				if(scancode == SDL_SCANCODE_D) dKeyPressed = true;
			}
			if (e.type == SDL_KEYUP){
				int scancode = e.key.keysym.scancode;
				if(scancode == SDL_SCANCODE_A) aKeyPressed = false;
				if(scancode == SDL_SCANCODE_W) wKeyPressed = false;
				if(scancode == SDL_SCANCODE_S) sKeyPressed = false;
				if(scancode == SDL_SCANCODE_D) dKeyPressed = false;
			}
			if( (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) || e.type == SDL_QUIT ) {
				quit = true;
			}	 
		}
		
		player.logic();

		SDL_RenderCopy(renderer, background->tex, NULL, NULL);
		player.draw();
		
		SDL_RenderPresent(renderer);
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
