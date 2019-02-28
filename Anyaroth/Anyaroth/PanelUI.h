#pragma once
#include "UIElement.h"
#include <vector>

class PanelUI : public UIElement
{
private:
	std::vector<UIElement*> _children;
public:
	PanelUI() {};
	virtual ~PanelUI();

	inline void addChild(UIElement* child) { _children.push_back(child); }
	inline std::vector<UIElement*>* getChildren() { return &_children; }

	virtual void render() const;
	virtual void update();
	virtual void handleEvent(const SDL_Event& event);
};

