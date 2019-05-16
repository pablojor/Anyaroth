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
	Melee(Game* g, Vector2D offset, Uint16 collidesWith, double damage, double w, double h, MeleeType id);
	virtual ~Melee() {}

	virtual void update(double deltaTime) {}
	virtual void meleeAttack(double x, double y, int dir);

	inline int getDamage() const { return _damage; }
	inline void setDamage(int dmg) { _damage = dmg; }
	void endMelee();

	inline void setOffset(const Vector2D& offset) { _offset = offset; }
	inline void setCollisionFilters(Uint16 collidesWith) { _collidesWith = collidesWith; }
	void setCollisionSize(const Vector2D& size);

	inline const MeleeType& getMeleeID() const { return _id; }

	inline bool isActive() const { return (_body != nullptr && _body->getBody() != nullptr &&  _body->getBody()->IsActive()); }
	void setActive(bool act) { if (_body != nullptr && _body->getBody() != nullptr) _body->getBody()->SetActive(act); }
};