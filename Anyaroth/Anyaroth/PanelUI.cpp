#include "PanelUI.h"
#include "Game.h"

PanelUI::PanelUI(Game* game) : UIElement(game)
{

}

PanelUI::~PanelUI()
{
	for (UIElement* e : _children) {
		delete e;
		e = nullptr;
	}
	_children.clear();
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

void PanelUI::update(double deltaTime)
{
	if (_visible)
		for (UIElement* e : _children)
			if (e->isVisible())
				e->update(deltaTime);
}

bool PanelUI::handleEvent(const SDL_Event & event)
{
	bool handled = false;
	if (_visible && _inputEnabled)
	{
		checkControlMode(event);

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

void PanelUI::checkControlMode(const SDL_Event & event)
{
	if (_game->usingJoystick() && _selectedButton != nullptr)
	{
		if (event.type == SDL_MOUSEMOTION)
		{
			_selectedButton->setSelected(false);
			SDL_ShowCursor(true);
			_game->changeControlMode();
		}
		else if (event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			if (!_selectedButton->isSelected())
			{
				SDL_WarpMouseGlobal(0, 0);
				_selectedButton->setSelected(true);
				SDL_ShowCursor(false);
			}

			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT && _selectedButton->getNextLeft() != nullptr)
				_selectedButton = _selectedButton->getNextLeft();
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP && _selectedButton->getNextUp() != nullptr)
				_selectedButton = _selectedButton->getNextUp();
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && _selectedButton->getNextRight() != nullptr)
				_selectedButton = _selectedButton->getNextRight();
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN && _selectedButton->getNextDown() != nullptr)
				_selectedButton = _selectedButton->getNextDown();
		}
	}
}
