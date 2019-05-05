#pragma once
#include "GameObject.h"
#include "Vector2D.h"

class Boss3;

class BossSensor : public GameObject
{
private:
	Boss3* _owner = nullptr;
	Vector2D _offset = Vector2D();
public:
	BossSensor(Game* g, Boss3* owner, Vector2D size, Vector2D offset);
	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual ~BossSensor();
};

