#pragma once
#include "Boss.h"
#include "LaserHandler.h"

class Boss2 : public Boss
{
private:
	LaserHandler* _lasers = nullptr;
	Vector2D _velocity = { 35,0 }, _originalVelocity = { 35,0 };

	int _dir, _onFloor = 0, _stopRange = 105;
	double _shootRange = 150, _speedIncrement = 100;
	bool _particles = false;

	Melee* _melee;

	int _timeStartMelee = 400, _timeOnMelee = 0;
	int _timeToShoot = 700, _timeWaiting = 0;
	int _timeToJump = 100, _timeWaitingJump = 0;
	bool _jump = false, _realMelee = false, fired = false;;

public:
	Boss2(Game* g, Player* player, Vector2D pos, BulletPool* pool);
	~Boss2() {}

	virtual void update(double deltaTime);

	void Jump();
	void checkJump(double deltaTime);

	virtual void movement(double deltaTime);
	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void endCollision(GameObject * other, b2Contact* contact);

	virtual void meleeAttack();
	inline void setLasers(LaserHandler* lasers) { _lasers = lasers; }
	void endJump();
	virtual void checkMelee(double deltaTime);
	virtual int getDamage() const { return _damage; }

	virtual void fase1(double deltaTime);
	virtual void fase2(double deltaTime);
	virtual void fase3(double deltaTime);
	virtual void beetwenFases(double deltaTime);
	virtual void manageLife(Life& l, int damage);

	virtual void die();
};