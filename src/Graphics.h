#pragma once

#include "Image.h"
#include <SDL.h>



class CGraphics {
	private:
		SDL_Renderer* m_renderer;
		float m_offsetX;
		float m_offsetY;
		CGraphics() = default;
	public:
		static CGraphics* init(SDL_Window* window);
		~CGraphics();

		void drawImageFullscreen(CImage* image);
		void drawImage(CImage* image, int posX, int posY, bool flip = false);
		void drawImageScaled(CImage* image, int posX, int posY, double w, double h, bool flip);
		void drawImageAtScale(CImage* image, int posX, int posY, int w, int h, bool flip);
		void drawImageSlice(image_islice_t image_slice, int posX, int posY, bool flip);
		void present();
		SDL_Renderer *getRenderer();

		void addScaling();
		void removeScaling();
		void getScaling(float& x, float& y);

		void setOffset(float x, float y);
		void getOffset(float &x, float &y);
};

class Animation {
};