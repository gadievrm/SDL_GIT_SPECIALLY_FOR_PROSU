#pragma once

#include "Entity.h"
#include "Graphics.h"
#include "Audio.h"
#include "Input.h"
#include "GameSystems.h"

#define GEM_ANIM_IDLE_FRAMES 5
#define GEM_ANIM_IDLE_INTERVAL 100
#define GEM_ANIM_PICKUP_FRAMES 4
#define GEM_ANIM_PICKUP_INTERVAL 250

class CGem : public ACEntity {
private:
    CAudio *m_audio;

    CImage *m_frames[GEM_ANIM_IDLE_FRAMES + GEM_ANIM_PICKUP_FRAMES];
    CSound *m_pickup_sound;

    uint64_t m_pickup_time;
    bool m_picked_up;
    double m_game_time;
public:
    CGem(GameSystems systems);
    void pickup();
    void logic(double dt) override;
    void draw(CGraphics *graphics) override;
};