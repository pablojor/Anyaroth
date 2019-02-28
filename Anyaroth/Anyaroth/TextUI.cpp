#include "TextUI.h"
#include "Game.h"



TextUI::TextUI(Game* game): UIElement(game)
{
	_text = "";
	_fontSize = 12;
	_font = Font(FONTS_PATH + "arial.ttf",_fontSize);
	_color = { 0, 0, 0, 255 };
	Texture texture = Texture(_game->getRenderer(), _text, &_font, _color);
	_destRect = { 0, 0, texture.getW(), texture.getH() };
}


TextUI::TextUI(Game* game, string text, SDL_Color color) : UIElement(game)
{
	_text = text;
	_fontSize = 12;
	_font = Font(FONTS_PATH + "arial.ttf", _fontSize);
	_color = color;
	Texture texture = Texture(_game->getRenderer(), _text, &_font, _color);
	_destRect = { 0, 0, texture.getW(), texture.getH() };
}

void TextUI::render() const
{
	if (_visible)
	{
		Texture texture = Texture(_game->getRenderer(), _text, &_font, _color);
		texture.render(_destRect);
	}
}

void TextUI::setPosition(int x, int y)
{
	_destRect.x = x;
	_destRect.y = y;
}

void TextUI::setSize(int w, int h)
{
	_destRect.w = w;
	_destRect.h = h;
}

void TextUI::setFont(string fontFile)
{
	_font = Font(FONTS_PATH + "arial.tff", _fontSize);
}
