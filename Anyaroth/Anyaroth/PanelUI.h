#pragma once
#include "UIElement.h"
#include <vector>

class PanelUI : public UIElement
{
protected:
	std::vector<UIElement*> _children;
	void addChild(UIElement* child);

public:
	PanelUI() : UIElement(nullptr) {}
	PanelUI(Game* game) {}
	virtual ~PanelUI();

	virtual void render() const;
	virtual void update();
	virtual void handleEvent(const SDL_Event& event);
};