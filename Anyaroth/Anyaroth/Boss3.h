#include "Boss.h"
#include "GravityBombCannon.h"

class Boss3 : public Boss
{
	private:
		int _dir = 0, _stopRange = 40;
		int _velocity = 8;

		//Cosas del disparo circular
		int _num = 0, _timeOnShooting = 0, _timeBeetwenBullets = 0, _timeBeetwenCircularShoot = 1000;
		int _numBullets = 40, _actualBullet = 0;
		double _angleIncrease = 360/ _numBullets, _angle = -90;

		void shoot();
		void shootBullet();
		void circularShoot(const double& deltaTime);

		//Cosas del disparo de agujeros negros
		GravityBombCannon* _gravGun = nullptr;
		void shootGrav();

		//Cosas del ataque Portal
		int timeToReapear = 2000, timeToShowPortal = 1000, _timeOut = 0;
		int _explosionRange = 60, _impulse = 15, _explosionDamage = 15;
		void portalAttack(const double& deltaTime);
		bool portalVisible = false;

	public:
		Boss3(Game* g, Player* player, Vector2D pos, BulletPool* pool);
		virtual ~Boss3();

		virtual void movement(const double& deltaTime);
		//virtual void beginCollision(GameObject* other, b2Contact* contact);
		//virtual void endCollision(GameObject * other, b2Contact* contact);

		//virtual void fase1(const double& deltaTime);
		virtual void fase2(const double& deltaTime);
		//virtual void fase3(const double& deltaTime);
		//virtual void beetwenFases(const double& deltaTime);
		//virtual void manageLife(Life& l, int damage);

};
