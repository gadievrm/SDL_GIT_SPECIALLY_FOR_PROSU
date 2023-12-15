#include <cmath>
#include "Player.h"
#include "Input.h"  // Добавлен новый заголовочный файл - It s a basic Artem

const int PLAYER_WIDTH  = 20;
const int PLAYER_HEIGHT = 23;
const float MOVE_SPEED  = 0.004;
const float FRICTION    = 0.995;

CPlayer::CPlayer(TGameSystems systems) {
    m_input = systems.input;

    // Важно ставить значения по-умолчанию
    // Иначе в значениях перемненных - мусор - sure
    m_velX = m_velY = 0.0;
    m_flipX = false;
    m_image = NULL;

    m_image = static_cast<CImage*>(systems.assets->fetchAsset(ASSET_TYPE_BITMAP, "data/gfx/sprites/player/idle/player-idle-1.png"));
}

bool CPlayer::getFlipX() {
    return m_flipX;
}

void CPlayer::logic(double dt) {
    if (m_input->getAKeyPressed()) {
        m_flipX = true;
        m_velX -= MOVE_SPEED * dt;
    }
    if (m_input->getDKeyPressed()) {
        m_flipX = false;
        m_velX += MOVE_SPEED * dt;
    }
    if (m_input->getWKeyPressed()) {
        m_velY -= MOVE_SPEED * dt;
    }
    if (m_input->getSKeyPressed()) {
        m_velY += MOVE_SPEED * dt;
    }

    setPosX(getPosX() + m_velX * dt);
    setPosY(getPosY() + m_velY * dt);

    m_velX *= pow(FRICTION, dt);
    m_velY *= pow(FRICTION, dt);
}

CImage *CPlayer::getImage() {
    return m_image;
}

void CPlayer::draw(CGraphics *graphics) {
    graphics->drawImage(m_image, getPosX(), getPosY(), getFlipX());
}
