#include "Input.h"
#include <optional>

CInput::CInput() :
m_last {},
m_now {},
m_mouse_x(0.0f),
m_mouse_y(0.0f)
{}

static std::optional<EKey> keyFromScancode(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
        switch (e.key.keysym.scancode) {
            case SDL_SCANCODE_A:
                return EKey::A;
            case SDL_SCANCODE_W:
                return EKey::W;
            case SDL_SCANCODE_S:
                return EKey::S;
            case SDL_SCANCODE_D:
                return EKey::D;
            case SDL_SCANCODE_LSHIFT:
            case SDL_SCANCODE_RSHIFT:
                return EKey::Shift;
            default:
                return std::nullopt;
        }
    }
    if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        switch (e.button.button) {
            case SDL_BUTTON_LEFT:
                return EKey::MouseLeft;
            case SDL_BUTTON_RIGHT:
                return EKey::MouseRight;
            default:
                return std::nullopt;
        }
    }

    return std::nullopt;
}

void CInput::processKeyEvent(SDL_Event& e) {
    std::optional<EKey> mbkey = keyFromScancode(e);

    if (!mbkey.has_value()) return;
    EKey key = mbkey.value();
    m_now[int(key)] = e.type == SDL_KEYDOWN;
}

void CInput::processMouseEvent(SDL_Event& e, float scaleX, float scaleY) {
    if (e.type == SDL_MOUSEMOTION) {
        SDL_MouseMotionEvent& ev_mouse_motion = e.motion;
        m_mouse_x = ev_mouse_motion.x * scaleX;
        m_mouse_y = ev_mouse_motion.y * scaleY;
    } else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        std::optional<EKey> mbkey = keyFromScancode(e);

        if (!mbkey.has_value()) return;
        EKey key = mbkey.value();
        m_now[int(key)] = e.type == SDL_MOUSEBUTTONDOWN;
    }
}

void CInput::update() {
    for (int i = 0; i < int(EKey::Count); i++) {
        m_last[i] = m_now[i];
    }
}

float CInput::getMouseX() {
    return m_mouse_x;
}

float CInput::getMouseY() {
    return m_mouse_y;
}

bool CInput::getHeld(EKey key) {
    return m_now[int(key)];
}

bool CInput::getReleased(EKey key) {
    return !m_now[int(key)] && m_last[int(key)];
}

bool CInput::getPressed(EKey key) {
    return m_now[int(key)] && !m_last[int(key)];
}