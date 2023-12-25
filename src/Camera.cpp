#include "Camera.h"
#include "GameSetup.h"

CCamera::CCamera() : 
m_mode(ECameraMode::Point),
m_posX(0.0),
m_posY(0.0),
m_desiredX(0.0),
m_desiredY(0.0),
m_smooth(false),
m_followed(NULL)
{}

void CCamera::getPos(float &x, float &y) {
    x = m_posX;
    y = m_posY;
}

void CCamera::setPos(float x, float y) {
    m_posX = x;
    m_posY = y;
}

void CCamera::update(double dt) {
    const float CAMERA_SMOOTH_FACTOR = 0.0042;
    float targetX;
    float targetY;

    switch (m_mode) {
        case ECameraMode::Point:
            targetX = m_desiredX;
            targetY = m_desiredY;
            break;
        case ECameraMode::Entity:
            targetX = m_followed->getPosX();
            targetY = m_followed->getPosY();
            break;
        default:
            return; // Not supposed to end up here
            break;
    }

    targetX -= GAME_WIDTH / 2;
    targetY -= GAME_HEIGHT / 2;

    if (m_smooth) {
        m_posX += (targetX - m_posX) * CAMERA_SMOOTH_FACTOR * dt;
        m_posY += (targetY - m_posY) * CAMERA_SMOOTH_FACTOR * dt;
    } else {
        m_posX = targetX;
        m_posY = targetY;
    }
}

void CCamera::followEntity(ACEntity *entity, bool smooth) {
    m_mode = ECameraMode::Entity;
    m_followed = entity;
    m_smooth = smooth;
}

void CCamera::lookAt(float x, float y, bool smooth) {
    m_mode = ECameraMode::Point;
    m_desiredX = x;
    m_desiredY = y;
    m_smooth = smooth;
}