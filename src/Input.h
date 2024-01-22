#pragma once
#include <SDL.h>

enum class EKey {
    W = 0,
    A,
    S,
    D,
    E,
    Tilde,
    Ctrl,
    Alt,
    Shift,
    MouseLeft,
    MouseRight,
    MouseMiddle,
    Count
};

class CInput {
private:
    bool m_last[int(EKey::Count)];
    bool m_now[int(EKey::Count)];
    bool m_mouse_focus;
    float m_mouse_x;
    float m_mouse_y;
    float m_mouse_z;

public:
    CInput();
    void processKeyEvent(SDL_Event& e);
    void processMouseEvent(SDL_Event& e, float scaleX, float scaleY);
    void update();

    // Key is being held
    bool getHeld(EKey key);

    // Key was just released
    bool getReleased(EKey key);

    // Key was just pressed
    bool getPressed(EKey key);

    bool getMouseFocus();
    float getMouseX();
    float getMouseY();
};
