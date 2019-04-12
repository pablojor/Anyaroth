#pragma once
#include "GameObject.h"
#include "BodyComponent.h"

class Melee : public GameObject
{
protected:
	BodyComponent* _body = nullptr;
	Vector2D _offset = {15,0}, _center;
	int _damage = 10, _w = 10, _h = 5, _r;
	int _dir;
	Uint16 _collidesWith;

public:
	Melee(Game* g, Vector2D offset, Uint16 collidesWith, double damage = 10, double w = 10, double h = 5);
	virtual ~Melee() {}

	virtual void update(const double& deltaTime) {}

	virtual void meleeAttack(double x, double y, int dir);
	int getDamage() const { return _damage; }
	void setDamage(int dmg) { _damage = dmg; }
	void endMelee();

	inline bool isActive() const { return (_body !=nullptr && _body->getBody() != nullptr &&  _body->getBody()->IsActive()); }
};