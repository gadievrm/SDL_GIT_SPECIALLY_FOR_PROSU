#include <cmath>
#include "Player.h"
#include "Input.h"  // Добавлен новый заголовочный файл - It s a basic Artem

const int PLAYER_WIDTH  = 20;
const int PLAYER_HEIGHT = 23;

CPlayer::CPlayer(TGameSystems systems) {
    // Systems
    m_input = systems.input;
    m_audio = systems.audio;

    CAssetManager *assets = systems.assets;

    //// Assets ////

    // Images
    m_i_idle.push_back(assets->fetchImage("sprites/player/idle/player-idle-1.png"));
    m_i_run.push_back(assets->fetchImage("sprites/player/run/player-run-1.png"));
    m_i_run.push_back(assets->fetchImage("sprites/player/run/player-run-2.png"));
    m_i_run.push_back(assets->fetchImage("sprites/player/run/player-run-3.png"));
    m_i_run.push_back(assets->fetchImage("sprites/player/run/player-run-4.png"));
    m_i_run.push_back(assets->fetchImage("sprites/player/run/player-run-5.png"));
    m_i_run.push_back(assets->fetchImage("sprites/player/run/player-run-6.png"));

    // Sounds
    m_steps_basic.push_back(assets->fetchSound("steps/basic-1.wav"));
    m_steps_basic.push_back(assets->fetchSound("steps/basic-2.wav"));
    m_steps_basic.push_back(assets->fetchSound("steps/basic-3.wav"));
    m_steps_basic.push_back(assets->fetchSound("steps/basic-4.wav"));
    m_steps_dirt.push_back(assets->fetchSound("steps/dirt-1.wav"));
    m_steps_dirt.push_back(assets->fetchSound("steps/dirt-2.wav"));
    m_steps_dirt.push_back(assets->fetchSound("steps/dirt-3.wav"));
    m_steps_dirt.push_back(assets->fetchSound("steps/dirt-4.wav"));
    m_steps_panel.push_back(assets->fetchSound("steps/panel-1.wav"));
    m_steps_panel.push_back(assets->fetchSound("steps/panel-2.wav"));
    m_steps_panel.push_back(assets->fetchSound("steps/panel-3.wav"));
    m_steps_panel.push_back(assets->fetchSound("steps/panel-4.wav"));
    m_steps_panel.push_back(assets->fetchSound("steps/panel-5.wav"));
    m_steps_wood.push_back(assets->fetchSound("steps/wood-1.wav"));
    m_steps_wood.push_back(assets->fetchSound("steps/wood-2.wav"));
    m_steps_wood.push_back(assets->fetchSound("steps/wood-3.wav"));
    m_steps_wood.push_back(assets->fetchSound("steps/wood-4.wav"));
    m_steps_stone.push_back(assets->fetchSound("steps/stone-1.ogg"));
    m_steps_stone.push_back(assets->fetchSound("steps/stone-2.ogg"));
    m_steps_stone.push_back(assets->fetchSound("steps/stone-3.ogg"));
    m_steps_stone.push_back(assets->fetchSound("steps/stone-4.ogg"));
    m_steps_water.push_back(assets->fetchSound("steps/water-1.wav"));
    m_steps_water.push_back(assets->fetchSound("steps/water-2.wav"));
    m_steps_water.push_back(assets->fetchSound("steps/water-3.wav"));
    m_steps_water.push_back(assets->fetchSound("steps/water-4.wav"));

    // State
    // Важно ставить значения по-умолчанию
    // Иначе в значениях перемненных - мусор - sure
    m_velX = m_velY = 0.0;
    m_flipX = false;

    m_step_phase = 0.0;
    m_walk_phase = 0.0;
    m_to_step = 0;
    m_time = 0.0;
    m_last_walk = m_time;
}

void CPlayer::init(TGameSystems systems) {
    // Entities
    m_world = static_cast<CWorld*>(systems.entities->findEntitiesByName("0world")[0]);
}

bool CPlayer::getFlipX() {
    return m_flipX;
}


#include <iostream>
void CPlayer::logic(double dt) {
    m_time += dt;

    //////////////// Controls ////////////////
    const float ACCELERATION  = 0.0012;
    const float RETENTION     = 0.991;
    const float SPEEDUP       = 0.8;
    static const float isqrt2 = 1.0 / sqrtf(2);

    bool running = m_input->getHeld(EKey::Shift);
    float multiplier = 1 + SPEEDUP * (running ? 1 : 0);
    float tomove = ACCELERATION * multiplier * dt;

    int hor = int(m_input->getHeld(EKey::D)) - int(m_input->getHeld(EKey::A));
    int ver = int(m_input->getHeld(EKey::S)) - int(m_input->getHeld(EKey::W));

    float moveX = hor * tomove;
    float moveY = ver * tomove;

    if (hor > 0) m_flipX = false;
    if (hor < 0) m_flipX = true;

    if (hor != 0 && ver != 0) {
        moveX *= isqrt2;
        moveY *= isqrt2;
    }

    ///////////// Movement physics ///////////////
    m_velX += moveX;
    m_velY += moveY;

    setPosX(getPosX() + m_velX * dt);
    setPosY(getPosY() + m_velY * dt);

    m_velX *= pow(RETENTION, dt);
    m_velY *= pow(RETENTION, dt);

    //////////////// Step sounds ////////////////
    if (hor != 0 || ver != 0) {
        double total_movement_acceleration = sqrtf(powf(moveX, 2) + powf(moveY, 2));
        doStepLogic(total_movement_acceleration, running);
    }

    //////// Walking/running animation //////////
    const double ENOUGH_MOVEMENT = 0.02;
    const double ADVANCE_FACTOR = 0.06;
    double total_velocity = sqrtf(powf(m_velX, 2) + powf(m_velY, 2)); 
    if (total_velocity >= ENOUGH_MOVEMENT) m_last_walk = m_time;
    m_walk_phase += ADVANCE_FACTOR * total_velocity;
    m_walk_phase -= floorf(m_walk_phase); // Cycle
}

void CPlayer::doStepLogic(float has_moved, bool running) {
    const float STEP_MULTIPLIER = 1.2; 
    const float RUN_ADDER = 0.5;
    m_step_phase += has_moved * (STEP_MULTIPLIER + ((running ? 1 : 0) * RUN_ADDER)) ;

    ETileMaterial mat = m_world->getTileMaterialAt(getPosX() + PLAYER_WIDTH/2, getPosY() + PLAYER_HEIGHT).value_or(ETileMaterial::Water);
    decltype(m_steps_basic)* steps = NULL;

    switch (mat) {
        case ETileMaterial::Dirt:
            steps = &m_steps_dirt;
            break;
        case ETileMaterial::Stone:
            steps = &m_steps_stone;
            break;
        case ETileMaterial::Panel:
            steps = &m_steps_panel;
            break;
        case ETileMaterial::Wood:
            steps = &m_steps_wood;
            break;
        case ETileMaterial::Basic:
            steps = &m_steps_basic;
            break;
        case ETileMaterial::Water:
            steps = &m_steps_water;
            break;
    }

    if (steps != nullptr && m_step_phase >= 1.0f) {
        m_to_step %= steps->size();
        m_audio->playSound((*steps)[m_to_step++]);
    }
    
    m_step_phase -= floorf(m_step_phase); // Cycle
}

void CPlayer::draw(CGraphics *graphics) {
    CImage *image;
    if (m_time - m_last_walk >= 80) {
        image = m_i_idle[0];
    } else {
        int frame = floorf(m_walk_phase * m_i_run.size()); 
        image = m_i_run[frame];
    }
    graphics->drawImageAtScale(image, getPosX(), getPosY(), PLAYER_WIDTH, PLAYER_HEIGHT, m_flipX);
}