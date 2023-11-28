#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Graphics.h"
#include "Entity.h"
#include "Player.h"

class Player;
class Game {
private:
    std::vector<Entity*> entities;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Player *mainPlayer;
    image_t *background;
    bool inited = false;
    bool quit = false;
    bool aKeyPressed;
    bool wKeyPressed;
    bool sKeyPressed;
    bool dKeyPressed;

    int framesCounted;
    uint64_t ticks;
    Uint64 frametime_now;
    Uint64 frametime_last;
    Uint64 performanceFrequency;

    Game() = default;

public:
    ~Game();
    static Game *init();
    void start();
    bool run();

    SDL_Renderer *getRenderer();
    bool getAKeyPressed();
    bool getWKeyPressed();
    bool getDKeyPressed();
    bool getSKeyPressed();
};