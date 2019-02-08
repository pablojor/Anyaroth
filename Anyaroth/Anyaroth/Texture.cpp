#include "Texture.h"


using namespace std;

typedef unsigned int uint;

void Texture::free() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}

void Texture::load(string filename, uint nRows, uint nCols) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr) throw SDLError();
	free();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr) throw SDLError();
	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect& destRect, double angle, SDL_Point anchor, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, &anchor, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, double angle, SDL_Point anchor, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, &anchor, flip);
}

void Texture::loadFromText(string text, const Font* font, SDL_Color color)
{
	SDL_Surface* textSurface = font->generateSurface(text, color);
	if (textSurface == nullptr) throw SDLError();
	free();
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (texture == nullptr)
	{
		w = h = 0;
		throw SDLError();
	}
	w = textSurface->w;
	h = textSurface->h;

	SDL_FreeSurface(textSurface);
}