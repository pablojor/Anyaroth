#include "Canvas.h"

void Canvas::render() const
{
	for (UIElement* e : _elements)
		e->render();
}

void Canvas::update()
{
	for (UIElement* e : _elements)
		e->update();
}

void Canvas::handleEvent(const SDL_Event& event)
{
	for (UIElement* e : _elements)
		e->handleEvent(event);
}
