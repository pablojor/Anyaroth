#pragma once
#include "Boss.h"
#include "BossPanel.h"
#include "Axe.h"

class ExplosiveBulletPool;
class BouncingBulletPool;

class Boss1 : public Boss
{
	private:
		Vector2D _amplitude = Vector2D(200,25), _velocity = Vector2D(0.5, 0.5), _dir = Vector2D(1,0);
		double  _damage = 50, _angularFrequency = 0.05, _k = _angularFrequency / _velocity.distance(Vector2D());

		//Cosas para el ataque bombardero
		ExplosiveBulletPool* _myExplosivePool = nullptr;
		Texture* _bombTexture = nullptr;
		int _bomberAttackTime = 2500, _timeOnBomberAttack = 0, _timeBeetwenBombs = 0,_bombRange = 1000;

		//Cosas Melee
		Melee* _melee;

		//Cosas de la ronda disparos
		bool ida = true;
		int _shootingTime = 2500,_timeOnShooting=0, _timeBeetwenBullets = 50;
		int _numBullets = 10, _actualBullet = 0, _dirB;
		double _angleIncrease = 7.5, _inicialAngle = 0,_angle=0;

		//Cosas del ataque orbe
		BouncingBulletPool* _myBouncingBulletPool = nullptr;
		int _numOrbs = 3, _actualNumOrbs = 0;

	private:
		void shoot();

	public:
		Boss1(Game* g, Player* player, Vector2D pos, BulletPool* pool, ExplosiveBulletPool* explosivePool, BouncingBulletPool* bouncingPool);
		virtual ~Boss1() {};

		virtual void update(const double& deltaTime);

		void movement(const double& deltaTime);
		void bomberAttack(const double& deltaTime,int t1, int t2);
		void meleeAttack();
		bool inline const isMeleeing() { return ((_anim->getCurrentAnim() == AnimatedSpriteComponent::EnemyAttack) && !_anim->animationFinished()); }
		void checkMelee();
		void armShoot(const double& deltaTime);

		void orbAttack();

		virtual void beginCollision(GameObject* other, b2Contact* contact);

		void fase1(const double& deltaTime);
		void fase2(const double& deltaTime);
		void fase3(const double& deltaTime);
		void beetwenFases(const double& deltaTime);
		void changeFase(int nextFase);

		void throwBomb();
		void throwOrb();
		void shootBullet();
		

};

