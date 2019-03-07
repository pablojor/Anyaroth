#pragma once
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Texture.h"

class GameComponent;

class FrameComponent : virtual public SpriteComponent
{
private:
	int _fil = 1, _col = 1;

public:
	FrameComponent(GameComponent* obj) : SpriteComponent(obj), RenderComponent(obj) {}
	virtual ~FrameComponent() {}

	virtual void render(Camera* c) const;
	void setFilAndCol(int fil, int col);
};