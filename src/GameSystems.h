#pragma once
#include "Input.h"
#include "Graphics.h"
#include "Audio.h"


struct GameSystems {
    Input *input;
    Graphics *graphics;
    Audio *audio;
};