#pragma once
#include "GameObject.h"
#include "Game.h"
#include <functional>

typedef void callback(Game*);

class MenuButton : public GameObject
{
private:
	Vector2D _pos;
	Texture* _texture = nullptr;
	callback* cb = nullptr;

public:
	MenuButton(Vector2D pos, Texture* texture, Game* g, callback* cb);
	virtual ~MenuButton() {}

	SDL_Rect getRect() const;
	bool handleEvent(const SDL_Event& event);
};