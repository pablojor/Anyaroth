#include "PanelUI.h"
#include "Game.h"

PanelUI::PanelUI(Game* game) : UIElement(game)
{

}

PanelUI::~PanelUI()
{
	for (UIElement* e : _children)
		delete e;
}

void PanelUI::addChild(UIElement* child)
{
	_children.push_back(child);
}

void PanelUI::removeChild(UIElement * child)
{
	_children.remove(child);
}

void PanelUI::removeAllChildren()
{
	for (auto child : _children)
		removeChild(child);
}

void PanelUI::render() const
{
	if (_visible)
		for (UIElement* e : _children)
			if (e->isVisible())
				e->render();
}

void PanelUI::update(const double& deltaTime)
{
	if (_visible)
		for (UIElement* e : _children)
			if (e->isVisible())
				e->update(deltaTime);
}

bool PanelUI::handleEvent(const SDL_Event & event)
{
	bool handled = false;
	if (_visible)
	{
		if (event.type == SDL_MOUSEMOTION && _selectedButton!= nullptr)
		{
			_selectedButton->setSelected(false);
			SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
			SDL_SetCursor(cursor);
		}
		auto it = _children.begin();

		while (!handled && it != _children.end())
		{
			if ((*it)->handleEvent(event))
				handled = true;
			else
				it++;
		}
	}

	return handled;
}