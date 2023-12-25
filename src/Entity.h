#pragma once

#include <string>
#include <SDL.h>
#include "Graphics.h"

class ACEntity;
#include "GameSystems.h"

class ACEntity {
private:
    std::string name;
    float posX;
    float posY;
    
public:
    float getPosX();
    float getPosY();
    void setPosX(float new_posX);
    void setPosY(float new_posY);
    virtual void init(TGameSystems systems) = 0;
    virtual void logic(double dt) = 0;
    virtual void draw(CGraphics *graphics) = 0;


    std::string getName();
    void setName(std::string new_name);
};