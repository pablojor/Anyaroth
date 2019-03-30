#pragma once
#include "GameObject.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"

class Laser : public GameObject
{
protected:
	SpriteComponent* _anim;
	TransformComponent* _transform;
	BodyComponent* _body = nullptr;
	Vector2D _pos;
	double _w, _h;
	int _damage, _angle;

public:
	Laser(Game* g, Vector2D pos, Texture* texture,double w, double h,double damage = 5);
	virtual ~Laser() {}

	virtual void update(const double& deltaTime) {}

	void Shoot(int angle);

	int const getDamage() { return _damage; }

	inline bool isActive() const { return (_body != nullptr && _body->getBody() != nullptr); }
};