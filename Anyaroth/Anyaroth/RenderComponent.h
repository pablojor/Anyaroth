#pragma once
#include "Component.h"

class GameObject;
class Camera;

class RenderComponent : public virtual Component
{
public:
	RenderComponent(GameObject* obj);
	virtual ~RenderComponent() {}

	virtual void render(Camera* c) const = 0;
};