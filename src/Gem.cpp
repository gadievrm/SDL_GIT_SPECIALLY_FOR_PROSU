#include <cstdio>
#include "Gem.h"

Gem::Gem(GameSystems systems) {
    char path[256];
    int loadedFrame = 0;

    for (int i = 1; i <= GEM_ANIM_IDLE_FRAMES; i++) {
        sprintf(path, "data/gfx/sprites/gem/gem-%d.png", i);
        frames[loadedFrame++] = systems.graphics->loadImage(path);
    }

    for (int i = 1; i <= GEM_ANIM_PICKUP_FRAMES; i++) {
        sprintf(path, "data/gfx/sprites/item-feedback/item-feedback-%d.png", i);
        frames[loadedFrame++] = systems.graphics->loadImage(path);
    }

    pickupTime = 0;
    pickedUp = false;
    aliveTime = 0;

    audio = systems.audio;

    pickupSound = audio->loadSound("data/sfx/pickup_bonus.wav");
}

int Gem::getCurrentFrame() {
    if (!pickedUp) {
        return ((int) ((aliveTime) / GEM_ANIM_IDLE_INTERVAL)) % GEM_ANIM_IDLE_FRAMES;
    } else {
        return GEM_ANIM_IDLE_FRAMES + (((int) ((aliveTime - pickupTime) / GEM_ANIM_PICKUP_INTERVAL)) % GEM_ANIM_PICKUP_FRAMES);
    }
}

void Gem::logic(double dt) {
    aliveTime += dt;
    if (aliveTime > 5000) pickup();
}

void Gem::draw(Graphics *graphics) {
    if (pickedUp && ((aliveTime - pickupTime) > (GEM_ANIM_PICKUP_FRAMES * GEM_ANIM_IDLE_INTERVAL))) return;

    double size = 2.0 - 1.0 * pickedUp;

    graphics->drawImageScaled(frames[getCurrentFrame()], getPosX(), getPosY(), size, size, false);
}

void Gem::pickup() {
    if (pickedUp) return;
    pickedUp = true;
    pickupTime = aliveTime;
    audio->playSound(pickupSound);
}