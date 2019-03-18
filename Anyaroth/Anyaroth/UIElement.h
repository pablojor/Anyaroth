#pragma once
#include "SDL.h"

class Game;

class UIElement
{
protected:
	bool _visible = true;
	Game* _game = nullptr;

public:
	UIElement() {}
	UIElement(Game* game);
	virtual ~UIElement() {}

	virtual void render() const = 0;
	virtual void update(double time) = 0;
	virtual void handleEvent(const SDL_Event& event) = 0;

	inline bool isVisible() const { return _visible; }
};