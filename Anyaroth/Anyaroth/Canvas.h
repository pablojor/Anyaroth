#pragma once
#include "UIElement.h"
#include <vector>

class Canvas
{
	private:
		std::vector<UIElement*> _elements;

	public:
		Canvas() {}
		virtual ~Canvas();

		virtual void render() const;
		virtual void update(double time);
		virtual void handleEvent(SDL_Event& event);

		inline virtual void addUIElement(UIElement* elem) { _elements.push_back(elem); }
};