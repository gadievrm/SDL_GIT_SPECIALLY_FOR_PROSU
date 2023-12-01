#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Graphics.h"
#include "Entity.h"
#include "Player.h"
#include "Input.h"

class Player;
class Game {
private:
    std::vector<Entity*> entities;
    SDL_Window* window;
    Player* mainPlayer;
    image_t* background;
    Graphics* graphics;
    Input input;
    bool inited;
    bool quit;

    int framesCounted;
    uint64_t ticks;
    Uint64 frametime_now;
    Uint64 frametime_last;
    Uint64 performanceFrequency;

    Game() = default;

public:
    ~Game();
    static Game* init();
    void start();
    bool run();

    Input* getInput();
};
