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
#include "DebugUI.h"
#include "Tileset.h"
#include "Camera.h"

class CGame {
private:
    // VIDEO
    SDL_Window* m_window;

    // Meta state
    CDebugUI* m_debug_ui;
    CGraphics* m_graphics;
    CInput m_input;
    CEntityManager m_entities;
    CAssetManager m_assets;

    // Game-specific stuff
    std::string m_map_name;
    CTileset *m_tileset;
    CPlayer* m_main_player;
    CCamera m_camera;

    // Cache of systems entities have access to
    TGameSystems m_systems;

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
