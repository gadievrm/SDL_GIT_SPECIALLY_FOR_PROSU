#include "ImageAssetLoader.h"

CImageAssetLoader::CImageAssetLoader(SDL_Renderer *renderer) : m_renderer(renderer)
{}

EAssetType CImageAssetLoader::getType() const {
    return ASSET_TYPE_BITMAP;
}

bool CImageAssetLoader::doesPathMatch(const std::string& path) const {
    // TODO: CHANGE
    return false;
}

ACAsset* CImageAssetLoader::loadAsset(const std::string& path) {
    SDL_Texture *texture;
	SDL_Surface *surface = NULL;
	surface = IMG_Load(path.c_str());

	if (surface == NULL) {
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	CImage *loadedImage = new CImage(path, texture, surface->w, surface->h);

	SDL_FreeSurface(surface);

	return loadedImage;
}