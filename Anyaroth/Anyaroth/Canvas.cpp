#include "Canvas.h"
#include "checkML.h"


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

void Canvas::update(const double& deltaTime)
{
	for (UIElement* e : _elements)
		e->update(deltaTime);
}

void Canvas::handleEvent(const SDL_Event& event)
{
	for (UIElement* e : _elements)
		e->handleEvent(event);
}