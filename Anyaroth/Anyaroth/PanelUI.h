#pragma once
#include "UIElement.h"
#include "ButtonUI.h"
#include <list>
#include <vector>

class PanelUI : public UIElement
{
protected:
	std::list<UIElement*> _children;
	void addChild(UIElement* child);
	void removeChild(UIElement* child);
	void removeAllChildren();

	std::vector<ButtonUI*> _buttons;
	int _selectedButton = 0;
public:
	PanelUI() : UIElement(nullptr) {}
	PanelUI(Game* game);
	virtual ~PanelUI();

	virtual void render() const;
	virtual void update(const double& deltaTime);
	virtual bool handleEvent(const SDL_Event& event);
};