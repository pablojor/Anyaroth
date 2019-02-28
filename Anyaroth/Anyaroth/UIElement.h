#pragma once
#include "SDL.h"

class UIElement
{
	protected:
		bool _visible = true;

	public:
		UIElement() {};
		virtual ~UIElement() {};

		virtual void render() const = 0;
		virtual void update() = 0;
		virtual void handleEvent(const SDL_Event& event) = 0;

		inline bool isVisible() { return _visible; }
};

