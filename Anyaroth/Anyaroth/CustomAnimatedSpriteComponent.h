#pragma once
#include "AnimatedSpriteComponent.h"

class CustomAnimatedSpriteComponent : public AnimatedSpriteComponent
{
private:
	//El estado del Sprite (para el cambio de color)
	enum States {Default, Hurt, Dead};
	States state = Default;

	double _timer = 0;
	double _hurtTime = 250;

public:
	CustomAnimatedSpriteComponent(GameObject* obj);
	virtual ~CustomAnimatedSpriteComponent() {};

	virtual void render(Camera* c) const;
	virtual void update(double deltaTime);

	void hurt() { state = Hurt; }
	void die() { state = Dead; }
};

