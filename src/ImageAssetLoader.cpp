#include "ImageAssetLoader.h"

CImageAssetLoader::CImageAssetLoader(SDL_Renderer *renderer) : m_renderer(renderer)
{}

EAsset CImageAssetLoader::getType() const {
    return EAsset::Image;
}

bool CImageAssetLoader::doesPathMatch(const std::filesystem::path& path) const {
    // TODO: CHANGE
    return false;
}

ACAsset* CImageAssetLoader::loadAsset(CAssetManager &assets, const std::filesystem::path& path) {
    SDL_Texture *texture;
	SDL_Surface *surface = NULL;
	surface = IMG_Load(path.string().c_str());

	if (surface == NULL) {
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	CImage *loadedImage = new CImage(path, texture, surface->w, surface->h);

	SDL_FreeSurface(surface);

	return loadedImage;
}