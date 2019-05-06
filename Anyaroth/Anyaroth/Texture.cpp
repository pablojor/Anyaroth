#include "Texture.h"

using namespace std;

typedef unsigned int uint;

void Texture::free()
{
	if (_texture != nullptr)
	{
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
	_w = _h = 0;
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(_texture, red, green, blue);
}

void Texture::load(string filename, uint nRows, uint nCols)
{
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

void Texture::load(int width, int height, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, width, height, 32, red, green, blue, alpha);
	if (tempSurface == nullptr) throw SDLError();
	free();
	_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	if (_texture == nullptr) throw SDLError();
	_numRows = 1;
	_numCols = 1;
	_w = tempSurface->w;
	_h = tempSurface->h;
	_fw = _w / _numCols;
	_fh = _h / _numRows;
	SDL_FreeSurface(tempSurface);

	SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);

	SDL_SetTextureColorMod(_texture, red, green, blue);
	SDL_SetTextureAlphaMod(_texture, alpha);
}

void Texture::render(const SDL_Rect& destRect, double angle, SDL_Point anchor, SDL_RendererFlip flip) const
{
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = _w; srcRect.h = _h;
	SDL_RenderCopyEx(_renderer, _texture, &srcRect, &destRect, angle, &anchor, flip);
}

void Texture::render(const SDL_Rect& destRect, const SDL_Rect& clipRect, double angle, SDL_Point anchor, SDL_RendererFlip flip) const
{
	SDL_RenderCopyEx(_renderer, _texture, &clipRect, &destRect, angle, &anchor, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, double angle, SDL_Point anchor, SDL_RendererFlip flip) const
{
	SDL_Rect srcRect;
	srcRect.x = _fw * col;
	srcRect.y = _fh * row;
	srcRect.w = _fw;
	srcRect.h = _fh;
	SDL_RenderCopyEx(_renderer, _texture, &srcRect, &destRect, angle, &anchor, flip);
}

void Texture::loadFromText(string text, const Font* font, SDL_Color color)
{
	if (text == "") text = " ";
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

/*void Texture::render(string text, const SDL_Rect& destRect, const Font* font, SDL_Color color) const
{
	// This creates the text surface
	SDL_Surface *stext = TTF_RenderText_Blended(font, text, color);

	// If it worked, then blit it to the main screen
	// If you wrap this function
	if (stext) {
		SDL_BlitSurface(stext, NULL,  , &destRect);
		// Very important for performance to free the text surface
		SDL_FreeSurface(stext);
	}
	else {
		throw
			string("Couldn't allocate text surface in printMessageAt");
	}
}*/