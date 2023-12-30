#include "Console.h"
#include <imgui.h>

CConsole gConsole;

constexpr int MAX_MESSAGES = 512;

CConsole::CConsole() :
m_n(0),
m_msgs {},
m_open(false),
m_scroll_to_last(false)
{}

void CConsole::update(TGameSystems systems) {
    if (systems.input->getPressed(EKey::Tilde))
        m_open = !m_open;
}

void CConsole::draw() {
    if (m_open) {
        ImGui::Begin("Console", &m_open);

        ImGui::BeginChild("ConsoleMessages");

        for (auto &msg : m_msgs) {
            ImVec4 color;
            switch (msg.type) {
                case ELog::Info:
                    color = ImVec4(1.0, 1.0, 1.0, 1.0);
                    break;
                case ELog::Debug:
                    color = ImVec4(0.6, 0.6, 1.0, 1.0);
                    break;
                case ELog::Warn:
                    color = ImVec4(0.7, 0.7, 0.1, 0.0);
                    break;
                case ELog::Error:
                    color = ImVec4(1.0, 0.2, 0.2, 0.0);
                    break;
            }
            ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::Text(msg.content.c_str());
            ImGui::PopStyleColor();
        }

        if (m_scroll_to_last || (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())) {
            ImGui::SetScrollHereY(1.0f);
            m_scroll_to_last = false;
        }

        ImGui::EndChild();
        
        ImGui::End();
    }
}

void CConsole::clear() {
    m_n = 0;
    m_msgs.clear();
}

void CConsole::addMessage(const TLogMessage& msg) {
    if (m_n++ == MAX_MESSAGES) {
        --m_n;
        m_msgs.pop_front();
    }
    m_msgs.push_back(msg);

    if (!m_open) m_scroll_to_last = true;
}

void CConsole::info(const std::string& what) {
    TLogMessage msg = {.type = ELog::Info, .content = what};
    addMessage(msg);
}

void CConsole::debug(const std::string& what) {
    TLogMessage msg = {.type = ELog::Debug, .content = what};
    addMessage(msg);
}

void CConsole::warn(const std::string& what) {
    TLogMessage msg = {.type = ELog::Warn, .content = what};
    addMessage(msg);
}

void CConsole::error(const std::string& what) {
    TLogMessage msg = {.type = ELog::Error, .content = what};
    addMessage(msg);
}