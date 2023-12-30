#pragma once
struct TGameSystems;

#include "Input.h"
#include "Graphics.h"
#include "Audio.h"
#include "EntityManager.h"
#include "AssetManager.h"

struct TGameSystems {
    CInput *input;
    CGraphics *graphics;
    CAudio *audio;
    CEntityManager *entities;
    CAssetManager *assets;
};