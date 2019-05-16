#pragma once
#include "PhysicsComponent.h"
#include "Bodycomponent.h"
#include "Game.h"
class GameObject;

class MovingComponent : public PhysicsComponent
{
private:
	BodyComponent* _body = nullptr;
	b2Vec2 _dir = b2Vec2(0.0f, 0.0f);
	uint32 _dashTimer = 0, _dashDur = 200;
	double _speed = 15, _jumpForce = 180, _gravScale = 3.5, _damping = 3.0;
	bool _dashing = false;

public:
	MovingComponent(GameObject* obj);
	~MovingComponent() {}

	virtual void update(double deltaTime);

	inline double getDirX() const { return _dir.x; }
	inline double getDirY() const { return _dir.y; }
	inline void changeDir(double x, double y) { _dir = b2Vec2(x, y); }
	void changeDash(bool dash);
	inline bool isDashing() const { return _dashing; }
};