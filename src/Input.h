#pragma once
#include <SDL.h>

class CInput {
private:
    bool m_a_key_pressed;
    bool m_w_key_pressed;
    bool m_s_key_pressed;
    bool m_d_key_pressed;
    float m_mouse_x;
    float m_mouse_y;

public:
    CInput();
    void processKeyEvent(SDL_Event& e);
    void processMouseEvent(SDL_Event& e, float scaleX, float scaleY);
    bool getAKeyPressed();
    bool getWKeyPressed();
    bool getSKeyPressed();
    bool getDKeyPressed();
    float getMouseX();
    float getMouseY();
};
