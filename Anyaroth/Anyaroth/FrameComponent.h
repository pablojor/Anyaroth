#pragma once
#include "SpriteComponent.h"


class FrameComponent : public SpriteComponent
{
private:
	int _fil = 1, _col = 1;

public:
	FrameComponent(GameObject* obj);
	virtual ~FrameComponent() {}

	virtual void render(Camera* c) const;
	void setFilAndCol(int fil, int col);
};