#pragma once

#include "Entity.h"
#include "Graphics.h"
#include "Input.h"
#include "GameSystems.h"

class CPlayer : public ACEntity {
private:
    CInput *m_input;

    CImage *m_image;

    float m_velX;
    float m_velY;
    bool m_flipX;

public:
    CPlayer(TGameSystems systems);

    bool getFlipX();
    CImage *getImage();

    void logic(double dt) override;
    void draw(CGraphics *graphics) override;
};