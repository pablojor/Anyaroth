#pragma once
#include "GameComponent.h"
#include "Game.h"
#include <functional>

typedef void callback(Game*);

class MenuButton : public GameComponent
{
private:
	Vector2D _pos;
	Texture* _texture;
	Game* g;
	callback* cb;

public:
	MenuButton(Vector2D pos, Texture* texture, Game* g, callback* cb);
	virtual ~MenuButton();

	SDL_Rect getRect();
	bool handleInput(const SDL_Event& event);
};