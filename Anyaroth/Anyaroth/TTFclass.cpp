#include "TTFclass.h"
#include <iostream>

Font::Font(string filename, int size)
{
	load(filename, size);
}

Font::~Font()
{
	free();
}

void Font::load(string filename, int size)
{
	_font = TTF_OpenFont(filename.c_str(), size);
	if (_font == nullptr) throw "Error loading font from " + filename;
}

void Font::free()
{
	if (_font != nullptr) TTF_CloseFont(_font);
	_font = nullptr;
}

SDL_Surface* Font::generateSurface(string text, SDL_Color color) const
{
	return TTF_RenderText_Solid(_font, text.c_str(), color);
}