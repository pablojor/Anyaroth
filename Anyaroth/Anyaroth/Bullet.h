#pragma once
#include "GameComponent.h"
#include "Vector2D.h"
#include "TransformComponent.h"

class Bullet : public GameComponent
{
private:
	int _range = 200; //rango del arma (en píxeles)
	int _aliveTime = 0; //tiempo que lleva vivo (usado en el rango)
	double _speed = 0;
	int _damage = 0;
	double _angle = 0;

	bool _collided = false;

	Vector2D _velocity = { 0,0 };
	Vector2D _iniPos = { 0,0 };

	TransformComponent* _trans = nullptr;

public:
	Bullet(Texture* texture, Vector2D iniPos, Game* g, string tag) : GameComponent(g, tag) {}
	Bullet() {}
	virtual ~Bullet() {}

	void beginCollision(GameComponent* other, b2Contact* contact);
	inline void setSpeed(double speed) { _speed = speed; }
	inline void setDamage(double damage) { _damage = damage; }
	inline int getDamage() const { return _damage; }
	inline void setVelocity(Vector2D vel) { _velocity = vel; }
	inline void setRotation(double rot) { _angle = rot; }

	void init(Texture* texture, double speed, int damage, double angle, int range = 5);
	virtual void update();
	void reset(Vector2D pos);
};