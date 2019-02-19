#pragma once
#include "GameComponent.h"
#include "Game.h"
#include <functional>

typedef void callback(Game*);

class MenuButton :
	public GameComponent
{
private:
	double _height;
	double _width;
	Vector2D _pos;

	Game* g;
	callback* cb;

public:
	MenuButton(Vector2D pos, double height, double width, Texture* texture, Game* g, callback* cb);
	virtual ~MenuButton();

	SDL_Rect getRect();
	void handleInput(const SDL_Event& event);
};