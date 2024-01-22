#include <iostream>
#include <fstream>
#include <ranges>
#include "GameSetup.h"
#include "Game.h"
#include "Gem.h"

#include "ImageAssetLoader.h"
#include "SoundAssetLoader.h"
#include "TilesetAssetLoader.h"
#include "Tileset.h"

#include "Map.h"

#include "DebugUI.h"

#include "Console.h"

#include <json.h>

namespace fs = std::filesystem;
using nlohmann::json;

CGame::CGame() : m_inited(false) {}

CGame* CGame::init() {
    CGame* game = new CGame();

    game->m_window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (game->m_window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        delete game;
        return nullptr;
    }

    game->m_graphics = CGraphics::init(game->m_window);
    SDL_Renderer *renderer = game->m_graphics->getRenderer();

    game->m_systems = {
        .input    = &game->m_input    ,
        .graphics =  game->m_graphics ,
        .audio    =  CAudio::init()   ,
        .entities = &game->m_entities ,
        .assets   = &game->m_assets   ,
        .physics  = &game->m_physics
    };

    game->m_assets.addLoader(*new CImageAssetLoader(renderer));
    game->m_assets.addLoader(*new CSoundAssetLoader());
    game->m_assets.addLoader(*new CTilesetAssetLoader(renderer));

    game->m_debug_ui = CDebugUI::init(game->m_window, renderer);

    game->m_editor = new CEditor(*game);

    game->m_inited = true;

    return game;
}

CGame::~CGame() {
    if (!m_inited) return;

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

    // startGaming();
    startMapEditor();
}

void CGame::loadMap(const std::filesystem::path& map_path) {
    MapLoad(m_systems, m_assets, map_path, m_map_name, m_entities);
    m_map_path = map_path;
}

void CGame::startMainMenu() {

}

void CGame::startGaming() {
    m_state = EGameState::Gaming;
    loadMap("out.json");
    m_main_player = static_cast<CPlayer*>(m_entities.findFirstByName("player0"));
    m_camera.followEntity(m_main_player, true);

    for (auto entity : m_entities.getAll()) {
        entity->init(m_systems);
    }
}

void CGame::startMapEditor() {
    m_state = EGameState::MapEditor;
    loadMap("out.json");
    m_world = static_cast<CWorld*>(m_entities.findFirstByName("0world"));
    m_tileset = &m_world->getTileset();

    // TODO: Maybe remove / change the initialization?
    for (auto entity : m_entities.getAll()) {
        entity->init(m_systems);
    }

    m_editor->begin();
}

void CGame::doMainMenu(double delta_time) {
    m_state = EGameState::MainMenu;
}

void CGame::doGaming(double delta_time) {
    // -----------------------------------------------------
    // -----------------------------------------------------
    //                      LOGIC
    // -----------------------------------------------------
    // -----------------------------------------------------
    for (auto entity : m_entities.getAll()) {
        entity->logic(delta_time);
    }
    m_camera.update(delta_time);

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                       OUTPUT
    // -----------------------------------------------------
    // -----------------------------------------------------
    float cameraX, cameraY;
    m_camera.getPos(cameraX, cameraY);
    m_graphics->setOffset(-cameraX, -cameraY);
    for (auto entity : m_entities.getAll()) {
        entity->draw(m_graphics);
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

    m_debug_ui->beginFrame();
    // ImGui::ShowDemoWindow();

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                        INPUT
    // -----------------------------------------------------
    // -----------------------------------------------------
    m_input.update();
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        m_debug_ui->handleEvent(e);
        
        if (!m_debug_ui->isTakingKeyboard() && e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            m_input.processKeyEvent(e);
        }

        if (!m_debug_ui->isTakingMouse()) {
            float scaleX, scaleY;
            m_graphics->getScaling(scaleX, scaleY);
            m_input.processMouseEvent(e, 1 / scaleX, 1 / scaleY);
        }

        if ((e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) || e.type == SDL_QUIT) {
            m_quit = true;
        }
    }

    gConsole.update(m_systems);
    switch (m_state) {
        case EGameState::MainMenu:
            doMainMenu(delta_time);
            break;
        case EGameState::MapEditor:
            m_editor->update(delta_time);
            break;
        case EGameState::Gaming:
            doGaming(delta_time);
            break;
    }
    gConsole.draw();

    m_graphics->removeScaling();
        m_debug_ui->endFrame();
    m_graphics->addScaling();

    m_graphics->present();

    return !m_quit;
}