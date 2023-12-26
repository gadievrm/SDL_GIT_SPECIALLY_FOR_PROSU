#include <iostream>
#include "GameSetup.h"
#include "Game.h"
#include "Gem.h"

#include "ImageAssetLoader.h"
#include "SoundAssetLoader.h"
#include "TilesetAssetLoader.h"
#include "Tileset.h"

#include "Map.h"

#include "DebugUI.h"

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
        .input          = &game->m_input    ,
        .graphics       =  game->m_graphics ,
        .audio          =  CAudio::init()   ,
        .entities       = &game->m_entities ,
        .assets         = &game->m_assets
    };

    game->m_assets.addLoader(*new CImageAssetLoader(renderer));
    game->m_assets.addLoader(*new CSoundAssetLoader());
    game->m_assets.addLoader(*new CTilesetAssetLoader(renderer));

    game->m_debug_ui = CDebugUI::init(game->m_window, renderer);

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

void CGame::startMainMenu() {

}

void CGame::startGaming() {
    m_state = EGameState::Gaming;
    MapLoad(m_systems, m_assets, "first.json", m_map_name, m_entities);
    m_main_player = static_cast<CPlayer*>(m_entities.findEntitiesByName("player0")[0]);
    m_camera.followEntity(m_main_player, true);

    for (auto entity : m_entities.getAllEntities()) {
        entity->init(m_systems);
    }
}

void CGame::startMapEditor() {
    m_state = EGameState::MapEditor;
    MapLoad(m_systems, m_assets, "first.json", m_map_name, m_entities);
    m_world = static_cast<CWorld*>(m_entities.findEntitiesByName("0world")[0]);
    m_tileset = &m_world->getTileset();
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
    for (auto entity : m_entities.getAllEntities()) {
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
    for (auto entity : m_entities.getAllEntities()) {
        entity->draw(m_graphics);
    }
}

void CGame::doMapEditor(double delta_time) {
    // -----------------------------------------------------
    // -----------------------------------------------------
    //                    USER INTERFACE
    // -----------------------------------------------------
    // -----------------------------------------------------
    ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::SetWindowSize(ImVec2(0, SCREEN_HEIGHT), ImGuiCond_Once);
        static int selected_tile = 0;
        ImGui::BeginTable("EditorMenuTiles", 4, 0, ImVec2(0.0, 0.0), 0.0);
        for (int i = 0; i < m_tileset->getSize(); i++) {
            image_slice_t slice = m_tileset->getTileImageSlice(i);
            float x = ((float) slice.x) / slice.image.getWidth();
            float y = ((float) slice.y) / slice.image.getHeight();
            float w = ((float) slice.w) / slice.image.getWidth();
            float h = ((float) slice.h) / slice.image.getHeight();
            bool selected = selected_tile == i;

            if (i % 4 == 0) ImGui::TableNextRow();
            ImGui::TableNextColumn();
            bool chosen = 
            ImGui::ImageButton(
                std::string("tile_").append(std::to_string(i)).c_str(),
                slice.image.getTexture(),
                ImVec2(slice.w, slice.h),
                ImVec2(x, y),
                ImVec2(x + w, y + h),
                ImVec4(0, 0, 0, 0),
                ImVec4(1, 1, selected ? 0.2 : 1, 1.0)
            );

            if (chosen) selected_tile = i;
        }
        ImGui::EndTable();
    ImGui::End();

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                        LOGIC
    // -----------------------------------------------------
    // -----------------------------------------------------
    float cameraX, cameraY;
    m_camera.getPos(cameraX, cameraY);
    int selected_tile_x = cameraX + m_input.getMouseX();
    int selected_tile_y = cameraY + m_input.getMouseY();
    m_world->convertToTileCoords(selected_tile_x, selected_tile_y);
    if (m_input.getHeld(EKey::MouseLeft)) {
        m_world->setTile(selected_tile_x, selected_tile_y, selected_tile);
    }

    m_camera.editor_update(m_systems);
    m_camera.update(delta_time);

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                       OUTPUT
    // -----------------------------------------------------
    // -----------------------------------------------------
    m_graphics->setOffset(-cameraX, -cameraY);
    for (auto entity : m_entities.getAllEntities()) {
        entity->draw(m_graphics);
    }

    m_world->drawTileInWorld(m_graphics, selected_tile, selected_tile_x, selected_tile_y);
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
            float scaleX;
            float scaleY;
            m_graphics->getScaling(scaleX, scaleY);
            m_input.processMouseEvent(e, 1 / scaleX, 1 / scaleY);
        }

        if ((e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) || e.type == SDL_QUIT) {
            m_quit = true;
        }
    }

    switch (m_state) {
        case EGameState::MainMenu:
            doMainMenu(delta_time);
            break;
        case EGameState::MapEditor:
            doMapEditor(delta_time);
            break;
        case EGameState::Gaming:
            doGaming(delta_time);
            break;
    }

    m_graphics->removeScaling();
    m_debug_ui->endFrame();
    m_graphics->addScaling();

    m_graphics->present();

    return !m_quit;
}