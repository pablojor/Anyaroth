#pragma once
#include "GameComponent.h"
#include "BodyComponent.h"

class Melee : public GameComponent
{
protected:
	BodyComponent* _body = nullptr;
	Vector2D _offset = {15,0}, _center;
	double _damage = 10, _w = 10, _h = 5, _r;
	int _dir;

public:
	Melee(Game* g);
	virtual ~Melee() {}

	virtual void update(double time) {}

	void meleeAttack(double x, double y, int dir);
	void beginCollision(GameComponent * other, b2Contact* contact);
	void endMelee();

	inline bool isActive() const { return (_body != nullptr && _body->getBody() != nullptr); }
};