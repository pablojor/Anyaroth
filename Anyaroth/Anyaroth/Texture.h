#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDLError.h"
#include "TTFclass.h"

#include <string>
#include <iostream>
#include <fstream>

#include "Component.h"

using namespace std;

typedef unsigned int uint;

class Texture : public Component
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

	string _filename = "";

public:
	Texture() :_renderer(nullptr) {}
	Texture(SDL_Renderer* r) : _renderer(r) {}
	Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1) : _filename(filename), _renderer(r) { load(filename, numRows, numCols); }
	Texture(SDL_Renderer* r, string text, const Font* font, SDL_Color color) : _renderer(r) { loadFromText(text, font, color); }
	~Texture() { free(); }
	void free();

	inline int getW() const { return _w; }
	inline int getH() const { return _h; }
	inline uint getNumCols() const { return _numCols; }
	inline uint getNumFils() const { return _numRows; }
	inline SDL_Texture* getTexture() const { return _texture; }

	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	void load(string filename, uint numRows = 1, uint numCols = 1);
	void load(int width, int height, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	void render(const SDL_Rect& rect, double angle = 0, SDL_Point anchor = { 0,0 }, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void render(const SDL_Rect& destRect, const SDL_Rect& clipRect, double angle = 0, SDL_Point anchor = { 0,0 }, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void renderFrame(const SDL_Rect& destRect, int row, int col, double angle = 0, SDL_Point anchor = { 0,0 }, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void loadFromText(string text, const Font* font, SDL_Color color);

	inline string getFilename() const { return _filename; };

	//void render(string text, const SDL_Rect& rect, const Font* font, SDL_Color color) const;
};