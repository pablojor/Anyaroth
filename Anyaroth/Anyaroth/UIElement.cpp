#include "UIElement.h"


UIElement::~UIElement()
{
	for (UIElement* e : _children)
		delete e;
}

void UIElement::render() const
{
	for (UIElement* e : _children)
	{
		if(e->_visible)
			e->render();
	}		
}

void UIElement::update()
{
	for (UIElement* e : _children)
	{
		if (e->_visible)
			e->update();
	}
}

void UIElement::handleEvent(const SDL_Event& event)
{
	for (UIElement* e : _children)
	{
		if (e->_visible)
			e->handleEvent(event);
	}
}