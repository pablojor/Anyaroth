#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"

class Bullet : public GameObject
{
protected:
	int _range = 200; //rango del arma (en pixeles)
	int _aliveTime = 0; //tiempo que lleva vivo (usado en el rango)
	double _speed = 0;
	int _damage = 0;

	bool _collided = false;

	Vector2D _iniPos = { 0,0 };

	Texture* _texture = nullptr;
	TransformComponent* _transform = nullptr;
	BodyComponent* _body = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;

public:
	Bullet(Game* game);
	virtual ~Bullet() {}

	virtual void beginCollision(GameObject* other, b2Contact* contact);
	inline void setSpeed(const double& speed) { _speed = speed; }
	inline void setDamage(const double& damage) { _damage = damage; }
	inline int getDamage() const { return _damage; }

	void init(Texture* texture, const Vector2D& position, const double& speed, const double& damage, const double& angle, const double& range, const string& tag);
	virtual void update(const double& deltaTime);
	void reset();
	void changeFilter();
};