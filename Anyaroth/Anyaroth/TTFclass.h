#pragma once
#include <SDL_ttf.h>
#include <string>

using namespace std;

class Font
{
private:
	TTF_Font* _font = nullptr;

public:
	Font() {}
	Font(string filename, int size);
	~Font();

	void load(string filename, int size);
	void free();
	SDL_Surface* generateSurface(string text, SDL_Color color) const;
	inline TTF_Font* getTTFFont() const { return _font; }
};