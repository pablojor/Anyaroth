#pragma once
#include "Interactable.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Missile.h"
#include "Boss1.h"

class MissileTurret : public Interactable
{
private:
	Boss1 * _boss = nullptr;

	bool ready = false, usable = true;
	int _activeFase;

public:
	MissileTurret(Game* g, Boss1* Boss, Vector2D pos, int activeFase);
	virtual ~MissileTurret() {}

	virtual void update(double deltaTime);
	bool interact();
};