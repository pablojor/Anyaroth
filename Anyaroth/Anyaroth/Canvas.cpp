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

void Canvas::update()
{
	for (UIElement* e : _elements)
		e->update();
}

void Canvas::handleEvent(SDL_Event& event)
{
	for (UIElement* e : _elements)
		e->handleEvent(event);
}