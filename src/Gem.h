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

class Gem : public Entity {
private:
    Audio *audio;

    image_t *frames[GEM_ANIM_IDLE_FRAMES + GEM_ANIM_PICKUP_FRAMES];
    sound_t *pickupSound;

    uint64_t pickupTime;
    bool pickedUp;
    double gameTime;
    
    int getCurrentFrame();

public:
    Gem(GameSystems systems);
    void pickup();
    virtual void logic(double dt);
    virtual void draw(Graphics *graphics);
};