#include <cmath>
#include "Player.h"
#include "Input.h"  // Добавлен новый заголовочный файл - It s a basic Artem

const int PLAYER_WIDTH  = 20;
const int PLAYER_HEIGHT = 23;

CPlayer::CPlayer(TGameSystems systems) {
    m_input = systems.input;
    m_audio = systems.audio;

    // Важно ставить значения по-умолчанию
    // Иначе в значениях перемненных - мусор - sure
    m_velX = m_velY = 0.0;
    m_flipX = false;

    m_walk_phase = 0.0;
    m_to_step = 0;

    // Assets
    m_image = static_cast<CImage*> (systems.assets->fetchAsset(EAsset::Image, "data/gfx/sprites/player/idle/player-idle-1.png"));
    m_steps_basic[0] = static_cast<CSound*>(systems.assets->fetchAsset(EAsset::Sound, "data/sfx/steps/basic-1.wav"));
    m_steps_basic[1] = static_cast<CSound*>(systems.assets->fetchAsset(EAsset::Sound, "data/sfx/steps/basic-2.wav"));
    m_steps_basic[2] = static_cast<CSound*>(systems.assets->fetchAsset(EAsset::Sound, "data/sfx/steps/basic-3.wav"));
    m_steps_basic[3] = static_cast<CSound*>(systems.assets->fetchAsset(EAsset::Sound, "data/sfx/steps/basic-4.wav"));
}

bool CPlayer::getFlipX() {
    return m_flipX;
}


#include <iostream>
void CPlayer::logic(double dt) {
    const float ACCELERATION  = 0.0012;
    const float RETENTION     = 0.991;
    const float SPEEDUP       = 0.8;
    const float isqrt2 = 1.0/sqrtf(2);

    float multiplier = 1 + SPEEDUP * (m_input->getShiftKeyPressed() ? 1 : 0);
    float tomove = ACCELERATION * multiplier * dt;

    int hor = 0;
    int ver = 0;
    if (m_input->getAKeyPressed()) {
        m_flipX = true;
        hor--;
    }
    if (m_input->getDKeyPressed()) {
        m_flipX = false;
        hor++;
    }
    if (m_input->getWKeyPressed()) {
        ver--;
    }
    if (m_input->getSKeyPressed()) {
        ver++;
    }

    float moveX = hor * tomove;
    float moveY = ver * tomove;

    if (hor != 0 && ver != 0) {
        moveX *= isqrt2;
        moveY *= isqrt2;
    }

    //////// Movement physics ////////
    m_velX += moveX;
    m_velY += moveY;

    setPosX(getPosX() + m_velX * dt);
    setPosY(getPosY() + m_velY * dt);

    m_velX *= pow(RETENTION, dt);
    m_velY *= pow(RETENTION, dt);
    //////////////////////////////////

    // Step
    if (hor != 0 || ver != 0)
        doStepLogic(sqrtf(powf(moveX, 2) + powf(moveY, 2)));
}

void CPlayer::doStepLogic(float tomove) {
    const float STEP_MULTIPLIER = 1.2; 
    m_walk_phase += tomove * STEP_MULTIPLIER;
    
    while (m_walk_phase >= 1.0f) {
        m_audio->playSound(m_steps_basic[m_to_step]);
        m_to_step = (m_to_step + 1) % 4;
        m_walk_phase -= 1.0f;
    }
}

CImage *CPlayer::getImage() {
    return m_image;
}

void CPlayer::draw(CGraphics *graphics) {
    graphics->drawImage(m_image, getPosX(), getPosY(), getFlipX());
}
