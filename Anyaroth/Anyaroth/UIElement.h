#pragma once
#include <vector>
#include "SDL.h"

class UIElement
{
	private:
		std::vector<UIElement*> _children;

	protected:
		bool _visible = true;

	public:
		UIElement() {};
		virtual ~UIElement();

		virtual void render() const = 0;
		virtual void update() = 0;
		virtual void handleEvent(const SDL_Event& event) = 0
			;
		inline virtual void addChild(UIElement* child) { _children.push_back(child); }
};

