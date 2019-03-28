#pragma once
#include "Interactable.h"
#include "Boss1.h"
#include "MisilBoss1.h"
class PlayState;
class AnimatedSpriteComponent;
class TransformComponent;
class BodyComponent;


class BotonLanzaMisiles : public Interactable
{
private:
	Boss1 * _boss = nullptr;

	PlayState* _play = nullptr;

	bool ready = false, usable = true;
public:
	BotonLanzaMisiles(Boss1* Boss, Game* g, PlayState* play, Texture* texture, Vector2D posIni);
	virtual void update(const double& deltaTime);
	virtual ~BotonLanzaMisiles();

	void interact();
};

