#include <SDL_image.h>
#include "Graphics.h"
#include "GameSetup.h"

CGraphics* CGraphics::init(SDL_Window *window) {
	CGraphics *graphics = new CGraphics();
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	graphics->addScaling();
	SDL_RenderSetVSync(renderer, 1);

	graphics->m_renderer = renderer;

	return graphics;
}

CGraphics::~CGraphics() {
	SDL_DestroyRenderer(m_renderer);
}

void CGraphics::drawImageFullscreen(CImage *image) {
	SDL_RenderCopy(m_renderer, image->getTexture(), NULL, NULL);
}

void CGraphics::drawImage(CImage *image, int posX, int posY, bool flip) {
	SDL_Rect dest_rect {.x = int(m_offsetX + posX), .y = int(m_offsetY + posY), .w = image->getWidth(), .h = image->getHeight()};

	SDL_RenderCopyEx(m_renderer, image->getTexture(), NULL, &dest_rect, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void CGraphics::drawImageScaled(CImage *image, int posX, int posY, double w, double h, bool flip) {
	SDL_Rect dest_rect {.x = int(m_offsetX + posX), .y = int(m_offsetY + posY), .w = ((int)(image->getWidth() * w)), .h = ((int)(image->getHeight() * h))};

	SDL_RenderCopyEx(m_renderer, image->getTexture(), NULL, &dest_rect, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void CGraphics::drawImageAtScale(CImage *image, int posX, int posY, int w, int h, bool flip) {
	SDL_Rect dest_rect {.x = int(m_offsetX + posX), .y = int(m_offsetY + posY), .w = w, .h = h};

	SDL_RenderCopyEx(m_renderer, image->getTexture(), NULL, &dest_rect, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void CGraphics::drawImageSlice(image_slice_t image_slice, int posX, int posY, bool flip) {
	const CImage& image = image_slice.image;

	SDL_Rect src_rect {.x = image_slice.x, .y = image_slice.y, .w = image_slice.w, .h = image_slice.h};
	SDL_Rect dest_rect {.x = int(m_offsetX + posX), .y = int(m_offsetY + posY), .w = image_slice.w, .h = image_slice.h};

	SDL_RenderCopyEx(m_renderer, image.getTexture(), &src_rect, &dest_rect, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void CGraphics::present() {
	SDL_RenderPresent(m_renderer);
}

SDL_Renderer* CGraphics::getRenderer() {
	return m_renderer;
}

void CGraphics::removeScaling() {
	SDL_RenderSetScale(m_renderer, 1, 1);
}

void CGraphics::addScaling() {
	SDL_RenderSetScale(m_renderer, ((float) SCREEN_WIDTH) / GAME_WIDTH, ((float) SCREEN_HEIGHT) / GAME_HEIGHT);
}

void CGraphics::getScaling(float& x, float& y) {
	SDL_RenderGetScale(m_renderer, &x, &y);
}

void CGraphics::setOffset(float x, float y) {
	m_offsetX = x;
	m_offsetY = y;
}

void CGraphics::getOffset(float &x, float &y) {
	x = m_offsetX;
	y = m_offsetY;
}