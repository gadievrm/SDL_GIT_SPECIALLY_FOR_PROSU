#include "Image.h"

CImage::CImage(std::optional<std::string> path, SDL_Texture *texture, int width, int height) {
    m_path = path;
    m_texture = texture;
    m_width = width;
    m_height = height;
}

int CImage::getWidth() {
    return m_width;
}

int CImage::getHeight() {
    return m_height;
}

SDL_Texture*& CImage::getTexture() {
    return m_texture;
}