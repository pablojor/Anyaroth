#include "Boss.h"
#include "GravityBombCannon.h"
#include "OrbShotgun.h"
#include "BossSensor.h"
#include "Boss3Panel.h"
#include "SpriteObject.h"

class FloatingHead;
class SpawnerBoss;

class BossCorpse : public GameObject
{
private:
	SpriteComponent* _sprite = nullptr;

public:
	BossCorpse(Game* g, Vector2D pos, Texture* texture);
};

class Boss3 : public Boss
{
private:
	int _stopRange = 30;
	int _velocity = 80;
	bool _invulnerable = false;
	Vector2D _dir = Vector2D(1, 0);
	Boss3Panel* _boss3Panel = nullptr;

	void handleAnimations(double time);

	//Cosas del disparo circular
	int _num = 0, _timeOnShooting = 0, _timeBeetwenBullets = 500, _timeBeetwenCircularShoot = 500;
	int _numBullets = 60, _actualBullet = 0;
	double _angleIncrease = 360 / _numBullets, _angle = 180;
	bool _needToFinishAnim = false;

	void shoot();
	void shootBullet(int numBullets, double angleIncrease);
	void circularShoot(double deltaTime);

	//Cosas de la fase soldado
	void AngraSoldierSpawn();
	BossCorpse* _corpse = nullptr;
	Gun* _otherGun = nullptr;
	void changeGun();

	int _numBulletsRifle = 0, _rifleBulletsCount = 0, _rifleCadence = 250;
	void rifleShoot();

	//Cosas del Dash
	double _dashTime = 500, _dashTimer = _dashTime, _gravity = 3, _damping = 3, _force = 40;
	bool _bulletApproaching = false;
	BossSensor* _sensor = nullptr;

	void dash();
	void checkDash(double deltaTime);

	//Cosas del salto
	double _jumpForce = 300;
	int _onFloor = 0;
	void jump();

	//Cosas del disparo de agujeros negros
	GravityBombCannon* _gravGun = nullptr;
	void shootGrav();
	int _timeToShoot = 900, _timeWaiting = 0;
	bool _alreadyShoot = false;

	//Cosas del ataque Portal
	int timeToReapear = 2000, timeToShowPortal = 1000, _timeOut = 0;
	int _explosionRange = 100, _impulse = 15, _explosionDamage = 25;
	void portalAttack(double deltaTime);
	bool portalVisible = false;
	bool realGone = false;

	// Cosas de la primera fase
	vector<SpawnerBoss*> _spawners;
	vector<FloatingHead*>_heads;

	bool _headTurn = false, _initSpawn = true, _alreadyDead = false;

	//Trono
	AnimatedSpriteComponent* _throneAnim = nullptr;

public:
	Boss3(Game* g, Player* player, Vector2D pos, BulletPool* pool);
	virtual ~Boss3();

	void setBoss3Panel(Boss3Panel* b);
	virtual void movement(double deltaTime);
	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void endCollision(GameObject * other, b2Contact* contact);

	inline void setBulletApproaching(bool bA) { _bulletApproaching = bA; }
	virtual void update(double deltaTime);
	virtual void fase1(double deltaTime);
	virtual void fase2(double deltaTime);
	virtual void fase3(double deltaTime);
	virtual void beetwenFases(double deltaTime);
	void subLife(int damage);
	virtual void die();

	void push_backSpawner(SpawnerBoss* spawner) { _spawners.push_back(spawner); }
	void push_backHead(FloatingHead* head) { _heads.push_back(head); }

	void setAnimThrone(AnimatedSpriteComponent* throneAnim) { _throneAnim = throneAnim; };
	void setAnimCorpse(BossCorpse* corp) { _corpse = corp; };
};