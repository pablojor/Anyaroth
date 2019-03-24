#include "Canvas.h"

Canvas::~Canvas()
{
	for (UIElement* e : _elements)
		delete e;
}

void Canvas::render() const
{
	for (UIElement* e : _elements)
		e->render();
}

void Canvas::update(double time)
{
	for (UIElement* e : _elements)
		e->update(time);
}

void Canvas::handleEvent(SDL_Event& event)
{
	for (UIElement* e : _elements)
		e->handleEvent(event);
}