#include <iostream>
#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Game* Game::init() {
    Game* game = new Game();

    game->window = SDL_CreateWindow("Almost Valorant", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (game->window == NULL) {
        std::cerr << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        delete game;
        return NULL;
    }

    game->graphics = Graphics::init(game->window);

    game->inited = true;

    return game;
}

Game::~Game() {
    if (!inited) return;

    delete graphics;
    SDL_DestroyWindow(window);
}

void Game::start() {
    if (!inited) {
        return;
    }

    quit = false;
    ticks = SDL_GetTicks64();
    framesCounted = 0;
    frametime_now = SDL_GetPerformanceCounter();
    frametime_last = 0;
    performanceFrequency = SDL_GetPerformanceFrequency();

    background = graphics->loadImage("data/gfx/environment/bg/back.png");
    mainPlayer = new Player(this);
    mainPlayer->setImage(graphics->loadImage("data/gfx/sprites/player/idle/player-idle-1.png"));
    mainPlayer->setPosX(SCREEN_WIDTH / 2 - mainPlayer->getImage()->w / 2);
    mainPlayer->setPosY(SCREEN_HEIGHT / 2 - mainPlayer->getImage()->h / 2);

    entities.push_back(mainPlayer);
}

bool Game::run() {
    if (quit || !inited) {
        return false;
    }

    frametime_last = frametime_now;
    frametime_now = SDL_GetPerformanceCounter();

    double deltaTime = (frametime_now - frametime_last) * 800.0 / performanceFrequency;

    if (SDL_GetTicks64() - ticks > 1000) {
        std::cout << "FPS: " << framesCounted << std::endl;
        framesCounted = 0;
        ticks = SDL_GetTicks64();
    }

    framesCounted++;

    
    while (SDL_PollEvent(&(input.e))) {
        if (input.e.type == SDL_KEYDOWN || input.e.type == SDL_KEYUP) input.processKeyEvent(input.e);

        if ((input.e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) || input.e.type == SDL_QUIT) {
            quit = true;
        }
    }

    for (auto entity : entities) {
        entity->logic(deltaTime);
    }

    graphics->drawImageFullscreen(background);
    for (auto entity : entities) {
        if (entity->isDrawable()){
            entity->draw(graphics);
        }
    }

    graphics->present();

    return !quit;
}

Input* Game::getInput() {
    return &input;
}