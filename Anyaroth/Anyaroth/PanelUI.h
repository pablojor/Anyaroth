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

	ButtonUI* _selectedButton = nullptr;
	bool _inputEnabled = true;
public:
	PanelUI() : UIElement(nullptr) {}
	PanelUI(Game* game);
	virtual ~PanelUI();

	virtual void render() const;
	virtual void update(double deltaTime);
	virtual bool handleEvent(const SDL_Event& event);

	virtual void checkControlMode(const SDL_Event& event);
};