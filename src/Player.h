#pragma once

#include "Entity.h"
#include "Graphics.h"
#include "Input.h"
#include "Audio.h"
#include "GameSystems.h"
#include "World.h"
#include "EntityEntries.h"

class CPlayer : public ACEntity {
private:
    // Systems
    CInput *m_input;
    CAudio *m_audio;

    // Assets
    std::vector<CImage*> m_i_idle;
    std::vector<CImage*> m_i_run;
    std::vector<CSound*> m_steps_basic;
    std::vector<CSound*> m_steps_stone;
    std::vector<CSound*> m_steps_dirt;
    std::vector<CSound*> m_steps_panel;
    std::vector<CSound*> m_steps_wood;
    std::vector<CSound*> m_steps_water;
    std::vector<CSound*> m_steps_sand;

    // Entities
    CWorld *m_world;

    // State
    float m_velX;
    float m_velY;
    bool m_flipX;
    double m_time;
    double m_last_walk;
    double m_step_phase;
    double m_walk_phase;
    int m_to_step;

    void doStepLogic(float tomove, bool running);

public:
    static inline const std::string CLASS_NAME = "player";
    static FEntityLoader Load;
    static FEntitySaver Save;

    CPlayer();

    bool getFlipX();

    void init(TGameSystems systems) override;
    void logic(double dt) override;
    void draw(CGraphics *graphics) override;
};