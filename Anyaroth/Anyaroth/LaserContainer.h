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

	virtual void update(const double& deltaTime) { GameObject::update(deltaTime); }

	void Warning() {  _anim->playAnim(AnimatedSpriteComponent::LaserOpening); }
	void Shoot(double angle) { _laser->Shoot(angle); }
	void Stop() { _laser->Stop();  _anim->playAnim(AnimatedSpriteComponent::LaserClosing);
	}
};