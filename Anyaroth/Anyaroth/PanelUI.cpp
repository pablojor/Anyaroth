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
		if (event.type == SDL_CONTROLLERBUTTONDOWN && _buttons.size() > 0)
		{
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT )
			{
				_buttons[_selectedButton]->setSelected(false);

				_selectedButton = (_selectedButton - 1) % _buttons.size();
				while (!_buttons[_selectedButton]->isVisible())
					_selectedButton = (_selectedButton - 1) % _buttons.size();

				_buttons[_selectedButton]->setSelected(true);
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
			{
				_buttons[_selectedButton]->setSelected(false);

				_selectedButton = (_selectedButton + 1) % _buttons.size();
				while (!_buttons[_selectedButton]->isVisible())
				{
					_selectedButton = (_selectedButton + 1) % _buttons.size();
				}

				_buttons[_selectedButton]->setSelected(true);
			}
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