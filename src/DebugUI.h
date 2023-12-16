#pragma once

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

class CDebugUI {
private:
    ImGuiContext* m_ctx;
    ImGuiIO *m_io;
    SDL_Window* m_window;
    CDebugUI() = default;
public:
    ~CDebugUI();
    static CDebugUI* init(SDL_Window *window, SDL_Renderer *renderer);
    void beginFrame();
    void handleEvent(SDL_Event &e);
    bool isTakingMouse();
    bool isTakingKeyboard();
    void endFrame();
};