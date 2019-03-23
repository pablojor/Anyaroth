#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "MovingComponent.h"
#include "CustomAnimatedSpriteComponent.h"
#include "Life.h"
#include "EnemyArm.h"
#include "PlayState.h"

class Enemy : public GameObject
{
protected:
	TransformComponent* _transform = nullptr;
	BodyComponent* _body = nullptr;
	MovingComponent* _movement = nullptr;
	CustomAnimatedSpriteComponent* _anim = nullptr;

	PlayState* _playstate = nullptr;

	Player* _player = nullptr;
	Vector2D _playerDistance;

	Life _life;
	bool _attacking = false, _dead = false;
	int _vision, _attackRangeX, _attackRangeY, _attackTime, _damage;
	double _time;
	float32 _speed;

public:
	Enemy(Game* g, PlayState* playstate, Texture* texture, Vector2D posIni, string tag);
	virtual ~Enemy() {}

	bool inCamera();
	bool inCameraOnlyX();

	virtual void beginCollision(GameObject* other, b2Contact* contact);

	virtual inline void noAttacking() { _attacking = false; }

	virtual void update(const double& deltaTime);

	void die();
	virtual void subLife(int damage);
	inline Life getLife() const { return _life; }

	inline int random(int low, int high) const { return low + (rand() % abs(high - low)); }

	void enemySpawn(Enemy* newEnemy);
};