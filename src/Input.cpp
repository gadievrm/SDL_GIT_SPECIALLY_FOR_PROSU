#include "Input.h"

Input input;

Input::Input() : aKeyPressed(false), wKeyPressed(false), sKeyPressed(false), dKeyPressed(false) {}

void Input::processInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        SDL_KeyboardEvent key = e.key;
        int scancode = e.key.keysym.scancode;
        if (scancode == SDL_SCANCODE_A) aKeyPressed = true;
        if (scancode == SDL_SCANCODE_W) wKeyPressed = true;
        if (scancode == SDL_SCANCODE_S) sKeyPressed = true;
        if (scancode == SDL_SCANCODE_D) dKeyPressed = true;
    }
    if (e.type == SDL_KEYUP) {
        int scancode = e.key.keysym.scancode;
        if (scancode == SDL_SCANCODE_A) aKeyPressed = false;
        if (scancode == SDL_SCANCODE_W) wKeyPressed = false;
        if (scancode == SDL_SCANCODE_S) sKeyPressed = false;
        if (scancode == SDL_SCANCODE_D) dKeyPressed = false;
    }
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
