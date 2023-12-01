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
    void processKeyEvent(SDL_Event& e);
    bool getAKeyPressed();
    bool getWKeyPressed();
    bool getSKeyPressed();
    bool getDKeyPressed();
};
