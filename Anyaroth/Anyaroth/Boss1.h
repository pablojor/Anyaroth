#pragma once
#include "Boss.h"
#include "BossSword.h"
#include "BossOrbCannon.h"
#include "BomberGun.h"

class Boss1 : public Boss
{
private:
	Vector2D _amplitude = Vector2D(150, 25), _velocity = Vector2D(0.8, 0.8), _dir = Vector2D(1, 0);
	double  _damage = 50, _angularFrequency = 0.05, _k = _angularFrequency / _velocity.distance(Vector2D());

	//Cosas para el ataque bombardero
	BomberGun* _bombGun = nullptr;
	int _bomberAttackTime = 2500, _timeOnBomberAttack = 0, _timeBeetwenBombs = 0, _bombRange = 1000;

	//Cosas Melee
	Melee* _melee;
	int _timeMelee = 900, _timeOnMelee = 0;

	//Cosas de la ronda disparos
	bool ida = true;
	int _shootingTime = 2500, _timeOnShooting = 0, _timeBeetwenBullets = 50;
	int _numBullets = 10, _actualBullet = 0, _dirB;
	double _angleIncrease = 7.5, _inicialAngle = 0, _angle = 0;

	//Cosas del ataque orbe
	BossOrbCannon* _orbGun = nullptr;
	int _numOrbs = 3, _actualNumOrbs = 0;

	void shoot();

public:
	Boss1(Game* g, Player* player, Vector2D pos, BulletPool* pool);
	virtual ~Boss1();

	virtual void update(double deltaTime);

	void movement(double deltaTime);
	void bomberAttack(double deltaTime, int t1, int t2);
	void meleeAttack();
	void checkMelee(double deltaTime);
	void armShoot(double deltaTime);

	void orbAttack();

	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void manageLife(Life& l, int damage);

	void fase1(double deltaTime);
	void fase2(double deltaTime);
	void fase3(double deltaTime);
	void beetwenFases(double deltaTime);
	void changeFase(int nextFase);

	void throwBomb();
	void throwOrb();
	void shootBullet();
};