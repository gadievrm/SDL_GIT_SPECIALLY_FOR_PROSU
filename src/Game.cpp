#include <iostream>
#include "Game.h"

//Screen dimension constants
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

Game *Game::init() {
	Game *game = new Game();

    //Create window
	game->window = SDL_CreateWindow("Almost Valorant", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
    if(game->window == NULL)
	{
		std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
		delete game;
		return NULL;
	}

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetVSync(game->renderer, 1);

    game->inited = true;

    return game;
}

Game::~Game() {
	if (!inited) return;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Game::start() {
    if (!inited) {
        return;
    }

	// Per-frame state
	quit = false;
	ticks = SDL_GetTicks64();
	framesCounted = 0;
	frametime_now = SDL_GetPerformanceCounter();
	frametime_last = 0;
	performanceFrequency = SDL_GetPerformanceFrequency();

	// Scene
	background = imageLoad("data/environment/Background/back.png", renderer);
    mainPlayer = new Player(this);
	mainPlayer->setImage(imageLoad("data/sprites/player/idle/playerIdle.png", renderer));
	mainPlayer->setPosX(SCREEN_WIDTH/2  - mainPlayer->getImage()->w / 2);
	mainPlayer->setPosY(SCREEN_HEIGHT/2 - mainPlayer->getImage()->h / 2);

    aKeyPressed = false;
    wKeyPressed = false;
    sKeyPressed = false;
    dKeyPressed = false;

	entities.push_back(mainPlayer);
}

bool Game::run() {
    if (quit || !inited) {
        return false;
    }

	frametime_last = frametime_now;
	frametime_now = SDL_GetPerformanceCounter();

	double deltaTime = (frametime_now - frametime_last)*1000.0 / performanceFrequency;

	if (SDL_GetTicks64() - ticks > 1000) {
		std::cout << "FPS: " << framesCounted << std::endl;
		framesCounted = 0;
		ticks = SDL_GetTicks64();
	}

	framesCounted++;

	SDL_Event e;
	while(SDL_PollEvent(&e)){ 
		if (e.type == SDL_KEYDOWN){
			SDL_KeyboardEvent key = e.key;
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
		if((e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) || e.type == SDL_QUIT ) {
			quit = true;
		}	 
	}

	for (auto entity : entities) {
		entity->logic(deltaTime);
	}
	
	SDL_RenderCopy(renderer, background->tex, NULL, NULL);
	for (auto entity : entities) {
		entity->draw();
	}
	
	SDL_RenderPresent(renderer);
	
	return !quit;
}

SDL_Renderer *Game::getRenderer() {
	return renderer;
}

bool Game::getAKeyPressed() {
	return aKeyPressed;
}

bool Game::getSKeyPressed() {
	return sKeyPressed;
}

bool Game::getWKeyPressed() {
	return wKeyPressed;
}

bool Game::getDKeyPressed() {
	return dKeyPressed;
}