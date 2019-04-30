#pragma once
#include "GameObject.h"
#include "BodyComponent.h"
#include "GunType_def.h"

class Melee : public GameObject
{
protected:
	BodyComponent* _body = nullptr;
	Vector2D _offset, _center;
	int _damage, _w, _h, _r, _dir;
	Uint16 _collidesWith;
	MeleeType _id;

public:
	Melee(Game* g, Vector2D offset, Uint16 collidesWith, double damage, double w, double h);
	virtual ~Melee() {}

	virtual void update(const double& deltaTime) {}
	virtual void meleeAttack(double x, double y, int dir);

	inline int getDamage() const { return _damage; }
	inline void setDamage(int dmg) { _damage = dmg; }
	void endMelee();
	inline const MeleeType& getId() const { return _id; }

	inline bool isActive() const { return (_body != nullptr && _body->getBody() != nullptr &&  _body->getBody()->IsActive()); }
};