#pragma once
#include <list>
#include "GameComponent.h"
#include "Life.h"
#include "EnemyArm.h"

class Player;
class PlayState;

class AnimatedSpriteComponent;
class MovingComponent;
class TransformComponent;
class BodyComponent;
class HurtRenderComponent;

class Enemy : public GameComponent
{
protected:
	AnimatedSpriteComponent* _anim = nullptr;
	MovingComponent* _movement = nullptr;
	TransformComponent* _transform = nullptr;
	Player* _player = nullptr;
	BodyComponent* _body = nullptr;
	HurtRenderComponent* _hurt = nullptr;

	PlayState* _play = nullptr;
	list<GameObject*>::iterator _itList;

	Life _life;
	bool _attacking = false, _dead = false;
	double _time;
	int _vision, _attackRange, _attackTime, _damage;
	float32 _speed;

public:
	Enemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~Enemy() {}

	bool inCamera();
	bool inCameraOnlyX();

	virtual void beginCollision(GameComponent* other, b2Contact* contact);

	void setItList(list<GameObject*>::iterator itFR);

	virtual inline void noLongerAttacking() { _attacking = false; }

	virtual void update(double time);

	void die();
	virtual void subLife(int damage);
	inline Life getLife() const { return _life; }

	inline int random(int low, int high) const { return low + (rand() % abs(high - low)); }

	void enemySpawn(Enemy* newEnemy);
};