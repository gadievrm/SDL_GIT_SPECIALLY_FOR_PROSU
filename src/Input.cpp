#include "Input.h"

CInput::CInput() : m_a_key_pressed(false), m_w_key_pressed(false), m_s_key_pressed(false), m_d_key_pressed(false), m_mouse_x(0.0f), m_mouse_y(0.0f) {}

void CInput::processKeyEvent(SDL_Event& e) {
    bool pressed = e.type == SDL_KEYDOWN;
    int scancode = e.key.keysym.scancode;

    if (scancode == SDL_SCANCODE_A) m_a_key_pressed = pressed;
    if (scancode == SDL_SCANCODE_W) m_w_key_pressed = pressed;
    if (scancode == SDL_SCANCODE_S) m_s_key_pressed = pressed;
    if (scancode == SDL_SCANCODE_D) m_d_key_pressed = pressed;
}

void CInput::processMouseEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEMOTION) {
        SDL_MouseMotionEvent& ev_mouse_motion = e.motion;
        m_mouse_x = ev_mouse_motion.x;
        m_mouse_y = ev_mouse_motion.y;
    }
}

bool CInput::getAKeyPressed() {
    return m_a_key_pressed;
}

bool CInput::getWKeyPressed() {
    return m_w_key_pressed;
}

bool CInput::getSKeyPressed() {
    return m_s_key_pressed;
}

bool CInput::getDKeyPressed() {
    return m_d_key_pressed;
}
