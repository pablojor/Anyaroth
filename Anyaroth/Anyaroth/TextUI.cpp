#include "TextUI.h"
#include "Game.h"

TextUI::TextUI(Game* game): UIElement(game)
{
	_text = "";
	_fontSize = 12;
	_font = game->getFont("ARIAL12");
	_color = { 0, 0, 0, 255 };
	_texture = new Texture(_game->getRenderer(), _text, _font, _color);
	_destRect = { 0, 0, _texture->getW(), _texture->getH() };
}

TextUI::TextUI(Game* game, string text, Font* font, uint fontSize, int xPos, int yPos, SDL_Color color) : UIElement(game)
{
	_text = text;
	_fontSize = fontSize;
	_font = font;
	_color = color;
	_texture = new Texture(_game->getRenderer(), _text, _font, _color);
	_destRect = { xPos, yPos, _texture->getW(), _texture->getH() };
}

void TextUI::render() const
{
	if (_visible)
	{
		SDL_Rect winRect = { _destRect.x * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X, _destRect.y * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y,
			_destRect.w * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X, _destRect.h * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y };

		_texture->render(winRect);
	}
}

void TextUI::setText(string text)
{
	_text = text;

	delete _texture;
	_texture = new Texture(_game->getRenderer(), _text, _font, _color);

	_destRect.w = _texture->getW();
	_destRect.h = _texture->getH();
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

void TextUI::setScale(float ratio)
{
	_destRect.w *= ratio;
	_destRect.h *= ratio;
}

void TextUI::setFont(string fontName, uint fontSize)
{
	_fontSize = fontSize;
	_font = _game->getFont(fontName);
}