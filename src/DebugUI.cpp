#include "DebugUI.h"

CDebugUI *CDebugUI::init(SDL_Window *window, SDL_Renderer *renderer) {
    ImGuiContext *ctx = ImGui::CreateContext();

    if (!ctx) {
        return nullptr;
    }

    if (!ImGui_ImplSDLRenderer2_Init(renderer)) {
        return nullptr;
    }

	if (!ImGui_ImplSDL2_InitForSDLRenderer(window, renderer)) {
        return nullptr;
    }

    CDebugUI *ui = new CDebugUI();
    ui->m_window = window;
    ui->m_ctx = ctx;
    return ui;
}

CDebugUI::~CDebugUI() {
    ImGui::DestroyContext(m_ctx);
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
}

void CDebugUI::beginFrame() {
    ImGui_ImplSDL2_NewFrame(m_window);
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui::NewFrame();
}

void CDebugUI::handleEvent(SDL_Event &e) {
    ImGui_ImplSDL2_ProcessEvent(&e);
}

void CDebugUI::endFrame() {
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}