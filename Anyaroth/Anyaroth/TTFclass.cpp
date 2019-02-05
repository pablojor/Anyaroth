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
	font = TTF_OpenFont(filename.c_str(), size);
	if (font == NULL) throw "Error loading font from " + filename;
}

void Font::free()
{
	if (font != NULL) TTF_CloseFont(font);
	font = NULL;
}

SDL_Surface* Font::generateSurface(string text, SDL_Color color) const
{
	return TTF_RenderText_Solid(font, text.c_str(), color);
}