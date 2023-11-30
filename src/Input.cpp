#include "Input.h"

Input::Input() : aKeyPressed(false), wKeyPressed(false), sKeyPressed(false), dKeyPressed(false) {}

void Input::processKeyEvent(SDL_Event& e) {
    bool pressed = e.type == SDL_KEYDOWN;
    int scancode = e.key.keysym.scancode;

    if (scancode == SDL_SCANCODE_A) aKeyPressed = pressed;
    if (scancode == SDL_SCANCODE_W) wKeyPressed = pressed;
    if (scancode == SDL_SCANCODE_S) sKeyPressed = pressed;
    if (scancode == SDL_SCANCODE_D) dKeyPressed = pressed;
}

bool Input::getAKeyPressed() {
    return aKeyPressed;
}

bool Input::getWKeyPressed() {
    return wKeyPressed;
}

bool Input::getSKeyPressed() {
    return sKeyPressed;
}

bool Input::getDKeyPressed() {
    return dKeyPressed;
}
