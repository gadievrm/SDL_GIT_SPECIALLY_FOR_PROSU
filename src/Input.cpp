#include "Input.h"

CInput::CInput() : a_key_pressed(false), w_key_pressed(false), s_key_pressed(false), d_key_pressed(false) {}

void CInput::processKeyEvent(SDL_Event& e) {
    bool pressed = e.type == SDL_KEYDOWN;
    int scancode = e.key.keysym.scancode;

    if (scancode == SDL_SCANCODE_A) a_key_pressed = pressed;
    if (scancode == SDL_SCANCODE_W) w_key_pressed = pressed;
    if (scancode == SDL_SCANCODE_S) s_key_pressed = pressed;
    if (scancode == SDL_SCANCODE_D) d_key_pressed = pressed;
}

bool CInput::getAKeyPressed() {
    return a_key_pressed;
}

bool CInput::getWKeyPressed() {
    return w_key_pressed;
}

bool CInput::getSKeyPressed() {
    return s_key_pressed;
}

bool CInput::getDKeyPressed() {
    return d_key_pressed;
}
