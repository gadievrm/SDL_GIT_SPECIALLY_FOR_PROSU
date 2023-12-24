#pragma once

#include "Entity.h"
#include "Graphics.h"
#include "Input.h"
#include "Audio.h"
#include "GameSystems.h"
#include "World.h"

class CPlayer : public ACEntity {
private:
    // Systems
    CInput *m_input;
    CAudio *m_audio;

    // Assets
    CImage *m_image;
    CSound *m_steps_basic[4];

    // Entities
    CWorld *m_world;

    // State
    float m_velX;
    float m_velY;
    bool m_flipX;
    double m_walk_phase;
    int m_to_step;

    void doStepLogic(float tomove);

public:
    CPlayer(TGameSystems systems);

    bool getFlipX();
    CImage *getImage();

    void logic(double dt) override;
    void draw(CGraphics *graphics) override;
};