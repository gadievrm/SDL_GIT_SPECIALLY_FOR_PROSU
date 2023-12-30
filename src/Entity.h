#pragma once

#include <optional>
#include <string>
#include <SDL.h>
#include "Graphics.h"

class ACEntity;
#include "GameSystems.h"

class ACEntity {
private:
    const std::string m_class_name;
    std::optional<std::string> m_name;
    float m_posX;
    float m_posY;

protected:
    ACEntity(const std::string& class_name);

public:
    float getPosX();
    float getPosY();
    void setPosX(float new_posX);
    void setPosY(float new_posY);
    virtual void init(TGameSystems systems) = 0;
    virtual void logic(double dt) = 0;
    virtual void draw(CGraphics *graphics) = 0;


    std::optional<std::string> getName();
    void setName(const std::string& new_name);
    const std::string& getClassName();
};