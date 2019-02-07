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
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	uint w = 0;
	uint h = 0;
	uint fw = 0; // Frame width
	uint fh = 0; // Frame height
	uint numCols = 1;
	uint numRows = 1;
	double angle = 0;
	SDL_Point anchor = { 0,0 };

public:
	Texture(SDL_Renderer* r) : renderer(r) {};
	Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1, double angle = 0, SDL_Point anchor = { 0,0 }) :
		renderer(r), angle(angle), anchor(anchor) {
		load(filename, numRows, numCols);
	};
	Texture(SDL_Renderer* r, string text, const Font* font, SDL_Color color) :
		renderer(r) {
		loadFromText(text, font, color);
	};
	~Texture() { free(); };
	void free();

	int getW() const { return w; };
	int getH() const { return h; };
	uint getNumCols() const { return numCols; };
	uint getNumFils() const { return numRows; };
	SDL_Texture* getTexture() const { return texture; };

	void load(string filename, uint numRows = 1, uint numCols = 1);
	void render(const SDL_Rect& rect, double angle = 0, SDL_Point anchor = { 0,0 }, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void renderFrame(const SDL_Rect& destRect, int row, int col, double angle = 0, SDL_Point anchor = { 0,0 }, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void loadFromText(string text, const Font* font, SDL_Color color);

};