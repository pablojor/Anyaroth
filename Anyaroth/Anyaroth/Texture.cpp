#include "Texture.h"


using namespace std;

typedef unsigned int uint;

void Texture::free() {
	SDL_DestroyTexture(_texture);
	_texture = nullptr;
	_w = _h = 0;
}

void Texture::load(string filename, uint nRows, uint nCols) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr) throw SDLError();
	free();
	_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	if (_texture == nullptr) throw SDLError();
	_numRows = nRows;
	_numCols = nCols;
	_w = tempSurface->w;
	_h = tempSurface->h;
	_fw = _w / _numCols;
	_fh = _h / _numRows;
	SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect& destRect, double angle, SDL_Point anchor,SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = _w; srcRect.h = _h;
	SDL_RenderCopyEx(_renderer, _texture, &srcRect, &destRect, angle, &anchor, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, double angle, SDL_Point anchor, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = _fw * col;
	srcRect.y = _fh * row;
	srcRect.w = _fw;
	srcRect.h = _fh;
	SDL_RenderCopyEx(_renderer, _texture, &srcRect, &destRect, angle, &anchor, flip);
}

void Texture::loadFromText(string text, const Font* font, SDL_Color color)
{
	SDL_Surface* textSurface = font->generateSurface(text, color);
	if (textSurface == nullptr) throw SDLError();
	free();
	_texture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	if (_texture == nullptr)
	{
		_w = _h = 0;
		throw SDLError();
	}
	_w = textSurface->w;
	_h = textSurface->h;

	SDL_FreeSurface(textSurface);
}