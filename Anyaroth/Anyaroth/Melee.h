#pragma once
#include "GameComponent.h"
#include "BodyComponent.h"

class Melee : public GameComponent
{
protected:
	Vector2D _offset = {15,0}, _center;
	double _damage = 10, _w = 10, _h = 5, _r;
	BodyComponent* _body = nullptr;
	int _dir;
public:
	Melee(Game* g);
	virtual void update(double time) {};
	void meleeAttack(double x, double y, int dir);
	void beginCollision(GameComponent * other, b2Contact* contact);
	void endMelee();
	inline const bool isActive() { return (_body != nullptr && _body->getBody() != nullptr); }
	virtual ~Melee();
};

