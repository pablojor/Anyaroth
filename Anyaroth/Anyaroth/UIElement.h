#pragma once
#include "SDL.h"

class Game;

class UIElement
{
	protected:
		bool _visible = true;
		Game* _game;

	public:
		UIElement(Game* game);
		virtual ~UIElement() {};

		virtual void render() const = 0;
		virtual void update() = 0;
		virtual void handleEvent(const SDL_Event& event) = 0;

		inline bool isVisible() { return _visible; }
};

