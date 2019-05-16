#include "Canvas.h"


Canvas::~Canvas()
{
	for (UIElement* e : _elements) {
		delete e;
		e = nullptr;
	}
	_elements.clear();
}

void Canvas::render() const
{
	for (UIElement* e : _elements)
		e->render();
}

void Canvas::update(double deltaTime)
{
	for (UIElement* e : _elements)
		e->update(deltaTime);
}

bool Canvas::handleEvent(const SDL_Event& event)
{
	bool handled = false;

	auto it = _elements.begin();

	while (!handled && it != _elements.end())
	{
		if ((*it)->handleEvent(event))
			handled = true;
		else
			it++;
	}	

	return handled;
}