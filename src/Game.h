#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Graphics.h"
#include "Audio.h"
#include "Entity.h"
#include "Player.h"
#include "Input.h"
#include "GameSystems.h"

class Game {
private:
    SDL_Window* window;

    Audio* audio;
    Graphics* graphics;
    Input input;
    GameSystems systems;

    std::vector<Entity*> entities;
    Player* mainPlayer;
    image_t* background;

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
};
