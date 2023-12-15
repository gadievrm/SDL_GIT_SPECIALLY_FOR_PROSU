#include <cstdio>
#include "Gem.h"

CGem::CGem(GameSystems systems) {
    char path[256];
    int loadedFrame = 0;
    CAssetManager *assets = systems.assets;

    for (int i = 1; i <= GEM_ANIM_IDLE_FRAMES; i++) {
        sprintf(path, "data/gfx/sprites/gem/gem-%d.png", i);
        m_frames[loadedFrame++] = static_cast<CImage*>(assets->fetchAsset(ASSET_TYPE_BITMAP, path));
    }

    for (int i = 1; i <= GEM_ANIM_PICKUP_FRAMES; i++) {
        sprintf(path, "data/gfx/sprites/item-feedback/item-feedback-%d.png", i);
        m_frames[loadedFrame++] = static_cast<CImage*>(assets->fetchAsset(ASSET_TYPE_BITMAP, path));
    }

    m_pickup_sound = static_cast<CSound*>(assets->fetchAsset(ASSET_TYPE_SOUND, "data/sfx/pickup_bonus.wav"));

    m_pickup_time = 0;
    m_picked_up = false;
    m_game_time = 0;

    m_audio = systems.audio;
}

static int getCurrentFrame(double game_time, bool picked_up, double pickup_time) {
    if (!picked_up) {
        return ((int) ((game_time) / GEM_ANIM_IDLE_INTERVAL)) % GEM_ANIM_IDLE_FRAMES;
    } else {
        return GEM_ANIM_IDLE_FRAMES + (((int) ((game_time - pickup_time) / GEM_ANIM_PICKUP_INTERVAL)) % GEM_ANIM_PICKUP_FRAMES);
    }
}

void CGem::logic(double dt) {
    m_game_time += dt;

    if (m_game_time >= 5000) pickup();
}

void CGem::draw(CGraphics *graphics) {
    if (m_picked_up && ((m_game_time - m_pickup_time) > (GEM_ANIM_PICKUP_FRAMES * GEM_ANIM_IDLE_INTERVAL))) return;

    double size = 2.0 - 1.0 * m_picked_up;

    graphics->drawImageScaled(m_frames[getCurrentFrame(m_game_time, m_picked_up, m_pickup_time)], getPosX(), getPosY(), size, size, false);
}

void CGem::pickup() {
    if (m_picked_up) return;
    m_picked_up = true;
    m_pickup_time = m_game_time;
    m_audio->playSound(m_pickup_sound);
}