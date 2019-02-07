#pragma once

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "SDLError.h"
#include "TTFclass.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned int uint;

class Texture
{
	private:
		SDL_Texture* _texture = nullptr;
		SDL_Renderer* _renderer = nullptr;
		uint _w = 0;
		uint _h = 0;
		uint _fw = 0; // Frame width
		uint _fh = 0; // Frame height
		uint _numCols = 1;
		uint _numRows = 1;

	public:
		Texture(SDL_Renderer* r) : _renderer(r) {};
		Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1) :
			_renderer(r) { load(filename, numRows, numCols); };
		Texture(SDL_Renderer* r, string text, const Font* font, SDL_Color color) :
			_renderer(r) { loadFromText(text, font, color); };
		~Texture() { free(); };
		void free();

		int getW() const { return _w; };
		int getH() const { return _h; };
		uint getNumCols() const { return _numCols; };
		SDL_Texture* getTexture() const { return _texture; };

		void load(string filename, uint numRows = 1, uint numCols = 1);
		void render(const SDL_Rect& rect, double angle = 0, SDL_Point anchor = {0,0}, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
		void renderFrame(const SDL_Rect& destRect, int row, int col, double angle = 0, SDL_Point anchor = {0,0}, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
		void loadFromText(string text, const Font* font, SDL_Color color);

};
