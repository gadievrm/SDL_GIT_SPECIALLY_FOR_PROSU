#pragma once
#include <SDL2/SDL.h>

class Input {
private:
    bool aKeyPressed;
    bool wKeyPressed;
    bool sKeyPressed;
    bool dKeyPressed;

public:
    Input();
    void processInput(SDL_Event& e);
    bool getAKeyPressed();
    bool getWKeyPressed();
    bool getSKeyPressed();
    bool getDKeyPressed();
};

extern Input input;
