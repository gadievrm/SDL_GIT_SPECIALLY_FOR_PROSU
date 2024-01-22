#include "Gem.h"

ACEntity* CGem::Load(std::optional<std::unordered_map<std::string, std::string>> options) {
    float x, y;

    if (options.has_value()) {
        auto opts = options.value();
        x = std::stof(opts["x"]);
        y = std::stof(opts["y"]);
    } else {
        x = 0;
        y = 0;
    }

    CGem *gem = new CGem();
    gem->m_posX = x;
    gem->m_posY = y;

    return gem;
}

std::unordered_map<std::string, std::string> CGem::Save(ACEntity *ent) {
    CGem *gem = static_cast<CGem*>(ent);
    return {
        {"x", std::to_string(gem->m_posX)},
        {"y", std::to_string(gem->m_posY)}
    };
}

CGem::CGem() : ACEntity(CGem::CLASS_NAME) {
    m_pickup_time = 0;
    m_picked_up = false;
    m_game_time = 0;
}

static int getCurrentFrame(double game_time, bool picked_up, double pickup_time) {
    if (!picked_up) {
        return ((int) ((game_time) / GEM_ANIM_IDLE_INTERVAL)) % GEM_ANIM_IDLE_FRAMES;
    } else {
        return GEM_ANIM_IDLE_FRAMES + (((int) ((game_time - pickup_time) / GEM_ANIM_PICKUP_INTERVAL)) % GEM_ANIM_PICKUP_FRAMES);
    }
}

void CGem::init(TGameSystems systems) {
    char path[256];
    int loadedFrame = 0;
    CAssetManager *assets = systems.assets;

    for (int i = 1; i <= GEM_ANIM_IDLE_FRAMES; i++) {
        sprintf(path, "sprites/gem/gem-%d.png", i);
        m_frames[loadedFrame++] = assets->fetchImage(path);
    }

    for (int i = 1; i <= GEM_ANIM_PICKUP_FRAMES; i++) {
        sprintf(path, "sprites/item-feedback/item-feedback-%d.png", i);
        m_frames[loadedFrame++] = assets->fetchImage(path);
    }

    m_pickup_sound = assets->fetchSound("pickup-bonus.wav");
    m_audio = systems.audio;
}

void CGem::logic(double dt) {
    m_game_time += dt;
}

void CGem::draw(CGraphics *graphics) {
    if (m_picked_up && ((m_game_time - m_pickup_time) > (GEM_ANIM_PICKUP_FRAMES * GEM_ANIM_IDLE_INTERVAL))) return;

    double size = 2.0 - 1.0 * m_picked_up;

    graphics->drawImageScaled(m_frames[getCurrentFrame(m_game_time, m_picked_up, m_pickup_time)], m_posX, m_posY, size, size, false);
}

void CGem::pickup() {
    if (m_picked_up) return;
    m_picked_up = true;
    m_pickup_time = m_game_time;
    m_audio->playSound(m_pickup_sound);
}