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
	virtual void update(double deltaTime);
	virtual bool handleEvent(const SDL_Event& event);

	inline virtual void addUIElement(UIElement* elem) { _elements.push_back(elem); }
};