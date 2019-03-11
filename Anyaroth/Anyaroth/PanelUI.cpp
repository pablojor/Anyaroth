#include "PanelUI.h"
#include "Game.h"

PanelUI::~PanelUI()
{
	for (UIElement* e : _children)
		delete e;
}

void PanelUI::addChild(UIElement* child)
{
	_children.push_back(child);
}

void PanelUI::render() const
{
	if (_visible)
		for (UIElement* e : _children)
			if (e->isVisible())
				e->render();
}

void PanelUI::update()
{
	if (_visible)
		for (UIElement* e : _children)
			if (e->isVisible())
				e->update();
}

void PanelUI::handleEvent(const SDL_Event & event)
{
	if (_visible)
		for (UIElement* e : _children)
			if (e->isVisible())
				e->handleEvent(event);
}