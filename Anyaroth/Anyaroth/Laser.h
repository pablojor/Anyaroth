#pragma once
#include "GameObject.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"

class Player;

class Laser : public GameObject
{
protected:
	SpriteComponent* _anim;
	TransformComponent* _transform;
	BodyComponent* _body = nullptr;
	Vector2D _pos;
	Player* _player;
	double _w, _h;
	int _damage, _angle;
	//Sistema de daño
	double startedDamaging = 301, timeToDmg = 300;
	bool colliding = false;

public:
	Laser(Game* g, Vector2D pos, Texture* texture, Player* player, double w, double h,double damage = 5);
	virtual ~Laser() {}

	virtual void update(const double& deltaTime);

	void Shoot(int angle);
	void Stop();
	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void endCollision(GameObject* other, b2Contact* contact);

	inline bool isActive() const { return (_body != nullptr && _body->getBody() != nullptr); }
};