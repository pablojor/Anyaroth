#pragma once
#include "UIElement.h"
#include <list>

class PanelUI : public UIElement
{
protected:
	std::list<UIElement*> _children;
	void addChild(UIElement* child);
	void removeChild(UIElement* child);
	void removeAllChildren();

public:
	PanelUI() : UIElement(nullptr) {}
	PanelUI(Game* game);
	virtual ~PanelUI();

	virtual void render() const;
	virtual void update(const double& deltaTime);
	virtual bool handleEvent(const SDL_Event& event);
};