#pragma once
#include "GameComponent.h"
#include "Boss1.h"
class PlayState;
class AnimatedSpriteComponent;
class TransformComponent;
class BodyComponent;
class MisilBoss1 :
	public GameComponent
{
private:
	AnimatedSpriteComponent* _anim = nullptr;
	TransformComponent* _transform = nullptr;
	Boss1 * _boss = nullptr;
	BodyComponent* _body = nullptr;

	PlayState* _play = nullptr;
public:
	MisilBoss1(Boss1* Boss, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~MisilBoss1();

	virtual void beginCollision(GameComponent* other, b2Contact* contact);

	virtual void update(double time);
};

