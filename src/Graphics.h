#pragma once

#include "Image.h"
#include <SDL.h>



class CGraphics {
	private:
		SDL_Renderer* m_renderer;
		CGraphics() = default;
	public:
		static CGraphics* init(SDL_Window *window);
		~CGraphics();

		void drawImageFullscreen(CImage *image);
		void drawImage(CImage *image, int posX, int posY, bool flip = false);
		void drawImageScaled(CImage *image, int posX, int posY, double w, double h, bool flip);
		void present();
		SDL_Renderer *getRenderer();

		void addScaling();
		void removeScaling();
};

class Animation {
};