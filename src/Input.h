#pragma once
#include <SDL.h>

class CInput {
private:
    bool a_key_pressed;
    bool w_key_pressed;
    bool s_key_pressed;
    bool d_key_pressed;

public:
    CInput();
    void processKeyEvent(SDL_Event& e);
    bool getAKeyPressed();
    bool getWKeyPressed();
    bool getSKeyPressed();
    bool getDKeyPressed();
};
