#pragma once
#include <string>
#include "Asset.h"

class IAssetLoader {
public:
    virtual EAsset getType() const = 0;
    virtual bool doesPathMatch(const std::string& path) const = 0;
    virtual ACAsset* loadAsset(const std::string& path) = 0;
};