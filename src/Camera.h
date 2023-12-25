#pragma once
#include "Entity.h"

enum class ECameraMode {
    Entity,
    Point
};

class CCamera {
private:
    ECameraMode m_mode;
    float m_posX;
    float m_posY;
    float m_desiredX;
    float m_desiredY;
    bool m_smooth;
    ACEntity *m_followed;

public:
    CCamera();
    void setPos(float x, float y);
    void getPos(float &x, float &y);
    void update(double dt);

    void followEntity(ACEntity *entity, bool smooth);
    void lookAt(float x, float y, bool smooth);
};