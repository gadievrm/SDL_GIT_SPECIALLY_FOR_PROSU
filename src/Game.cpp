#include <iostream>
#include "Game.h"
#include "Gem.h"

#include "ImageAssetLoader.h"
#include "SoundAssetLoader.h"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

CGame::CGame() : m_inited(false) {}

CGame* CGame::init() {
    CGame* game = new CGame();

    game->m_window = SDL_CreateWindow("Almost Valorant", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (game->m_window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        delete game;
        return nullptr;
    }

    game->m_graphics = CGraphics::init(game->m_window);
    SDL_Renderer *renderer = game->m_graphics->getRenderer();

    game->m_systems = {
        .input          = &game->m_input    ,
        .graphics       =  game->m_graphics ,
        .audio          =  CAudio::init()   ,
        .entities       = &game->m_entities ,
        .assets         = &game->m_assets
    };

    game->m_assets.addLoader(*new CImageAssetLoader(renderer));
    game->m_assets.addLoader(*new CSoundAssetLoader());

    // IMGUI
    game->m_imgui_ctx = ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(game->m_window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    game->m_inited = true;

    return game;
}

CGame::~CGame() {
    if (!m_inited) return;

    ImGui::DestroyContext(m_imgui_ctx);
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();

    delete m_graphics;
    SDL_DestroyWindow(m_window);
}

void CGame::start() {
    if (!m_inited) {
        return;
    }

    m_quit = false;
    m_ticks = SDL_GetTicks64();
    m_frames_counted = 0;
    m_frametime_last = SDL_GetPerformanceCounter();
    m_performance_frequency = SDL_GetPerformanceFrequency();

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                     WORLD LOADING
    // -----------------------------------------------------
    // -----------------------------------------------------
    m_background = static_cast<CImage*>(m_assets.fetchAsset(ASSET_TYPE_BITMAP, "data/gfx/environment/bg/back.png"));

    m_main_player = new CPlayer(m_systems);
    m_main_player->setPosX(SCREEN_WIDTH  / 2 - m_main_player->getImage()->getWidth() / 2);
    m_main_player->setPosY(SCREEN_HEIGHT / 2 - m_main_player->getImage()->getHeight() / 2);
    m_entities.addEntityWithName("000player", *m_main_player);
    
    {
        auto width    = 1;
        auto height   = 1;
        auto x_offset = 120;
        auto y_offset = 120;
        auto x_gap    = 30;
        auto y_gap    = 30;
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                CGem *gem = new CGem(m_systems);
                gem->setPosX(x_offset + x_gap * i);
                gem->setPosY(y_offset + y_gap * j);
                m_entities.addEntity(*gem);
            }
        }
    }
}

bool CGame::run() {
    if (m_quit || !m_inited) {
        return false;
    }

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                  TIME & PERFORMANCE
    // -----------------------------------------------------
    // -----------------------------------------------------
    double frametime_now = SDL_GetPerformanceCounter();
    double delta_time = (frametime_now - m_frametime_last) * 1000.0 / m_performance_frequency;
    m_frametime_last = frametime_now;
    if (SDL_GetTicks64() - m_ticks > 1000) {
        m_frames_counted = 0;
        m_ticks = SDL_GetTicks64();
    }
    m_frames_counted++;

    ImGui_ImplSDL2_NewFrame(m_window);
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                        INPUT
    // -----------------------------------------------------
    // -----------------------------------------------------
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        ImGui_ImplSDL2_ProcessEvent(&e);
        if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) m_input.processKeyEvent(e);

        if ((e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) || e.type == SDL_QUIT) {
            m_quit = true;
        }
    }

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                      LOGIC
    // -----------------------------------------------------
    // -----------------------------------------------------
    for (auto entity : m_entities.getAllEntities()) {
        entity->logic(delta_time);
    }

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                       OUTPUT
    // -----------------------------------------------------
    // -----------------------------------------------------
    m_graphics->drawImageFullscreen(m_background);
    for (auto entity : m_entities.getAllEntities()) {
        entity->draw(m_graphics);
    }

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

    m_graphics->present();

    return !m_quit;
}