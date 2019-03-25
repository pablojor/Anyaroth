#pragma once
#include "GameComponent.h"
#include "Boss1.h"
#include "MisilBoss1.h"
class PlayState;
class AnimatedSpriteComponent;
class TransformComponent;
class BodyComponent;


class BotonLanzaMisiles :
	public GameComponent
{
private:
	AnimatedSpriteComponent* _anim = nullptr;
	TransformComponent* _transform = nullptr;
	Boss1 * _boss = nullptr;
	BodyComponent* _body = nullptr;

	PlayState* _play = nullptr;

	bool ready = true, _ableToFire=false;
public:
	BotonLanzaMisiles(Boss1* Boss, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~BotonLanzaMisiles();
	virtual void beginCollision(GameComponent* other, b2Contact* contact);
	virtual void endCollision(GameComponent * other, b2Contact* contact);
	virtual void update(const double& deltaTime);

	void shoot();
};

