#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "CustomAnimatedSpriteComponent.h"
#include "Player.h"
#include "Life.h"
#include "ParticleManager.h"

class Enemy : public GameObject
{
protected:
	TransformComponent* _transform = nullptr;
	BodyComponent* _body = nullptr;
	CustomAnimatedSpriteComponent* _anim = nullptr;
	Texture* _texture;

	Player* _player = nullptr;
	Vector2D _playerDistance;

	Life _life;
	Texture * _hurtParticle = nullptr;

	bool _attacking = false, _drop = true, _dropMelee = false, _stunned = false, _spawnParticles = false;
	int _vision, _attackRangeX, _attackRangeY, _attackTime, _damage;
	double _time;
	float32 _speed;
	
	b2Vec2 _contactPoint = b2Vec2_zero;

	int _coinValue = 10;

	string _deathSound = "", _hitSound = "", _meleeHit = "";

public:
	Enemy(Game* g, Player* player, Vector2D pos, Texture* texture, string death = "", string hit = "", string meleeHit = "");
	virtual ~Enemy() {}

	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void update(double deltaTime);

	inline void stopAttacking() { _attacking = false; }

	virtual void die();
	virtual void drop();

	virtual void subLife(int damage);
	inline Life getLife() const { return _life; }

	inline bool isStunned() { return _stunned; }
	inline void setStunned(bool value) { _stunned = value; }

	bool inCamera();
};