#pragma once
#include <SDL.h>
#include <vector>
#include "Graphics.h"
#include "Audio.h"
#include "Entity.h"
#include "Player.h"
#include "Input.h"
#include "GameSystems.h"
#include "EntityManager.h"
#include "AssetManager.h"

#include <imgui.h>

class CGame {
private:
    // VIDEO
    SDL_Window* m_window;

    // Meta state
    ImGuiContext *m_imgui_ctx;
    CGraphics* m_graphics;
    CInput m_input;
    CEntityManager m_entities;
    CAssetManager m_assets;

    // Cache of systems entities have access to
    TGameSystems m_systems;

    // Level state (TODO: remove by integrating into world/entities)
    CPlayer* m_main_player;
    CImage* m_background;

    // Basic state
    bool m_inited;
    bool m_quit;

    // Time & performance metrics
    int m_frames_counted;
    uint64_t m_ticks;
    Uint64 m_frametime_last;
    Uint64 m_performance_frequency;

    CGame();

public:
    ~CGame();
    static CGame* init();
    void start();
    bool run();
};
