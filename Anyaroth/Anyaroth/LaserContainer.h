#pragma once
#include "GameObject.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Laser.h"

class LaserContainer : public GameObject
{
private:
	Vector2D _pos;
	Laser* _laser;
	AnimatedSpriteComponent* _anim;

public:
	LaserContainer(Game* g, Vector2D pos, Texture* container, Texture* laser, Player* player);
	virtual ~LaserContainer() {}

	virtual void update(double deltaTime) { GameObject::update(deltaTime); }

	void Warning(double angle) { _laser->PreShoot(angle); _anim->playAnim(AnimatedSpriteComponent::LaserOpening); }
	void Shoot() { _laser->Shoot(); }
	void Stop() { _laser->Stop();  _anim->playAnim(AnimatedSpriteComponent::LaserClosing);	}

	virtual void render(Camera* c) const;
};