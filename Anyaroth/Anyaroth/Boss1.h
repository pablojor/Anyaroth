#pragma once
#include "DistanceEnemy.h"
#include "BossPanel.h"
#include "Axe.h"

class ExplosiveBulletPool;

class Boss1 : public DistanceEnemy
{
	private:

		bool _fase1 = true, _fase2 = false, _fase3 = false, _beetwenFase = false, move= true;
		Vector2D _bodyPos, _playerPos, _originalPos, _amplitude = Vector2D(200,25), _velocity = Vector2D(0.5, 0.5), _dir = Vector2D(1,0);
		double  _damage = 50, _angularFrequency = 0.05, _k = _angularFrequency / _velocity.distance(Vector2D());
		int _lastFase = 0;

		BodyComponent* _playerBody;

		//Vida
		Life _life1, _life2, _life3;

		//Panel del HUD
		BossPanel* _bossPanel = nullptr;

		//Cosas para el ataque bombardero
		ExplosiveBulletPool* _myExplosivePool = nullptr;
		Texture* _bombTexture = nullptr;
		bool _bomberAttacking = false;
		int _bomberAttackTime = 2500, _timeOnBomberAttack = 0, _timeBeetwenBombs = 0,_bombRange = 1000;

		//Cosas Melee
		Melee* _melee;

		//Tiempo entre acciones
		int _doSomething = 1000, _noAction = 0;

		//Cosas del ataque orbe
		bool _orbAttacking = false;
		int _numOrbs = 3, _actualNumOrbs = 0;

	public:
		Boss1(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool, ExplosiveBulletPool* explosivePool);
		virtual ~Boss1() {};

		void setBossPanel(BossPanel* b);

		virtual void update(const double& deltaTime);

		virtual void subLife(int damage);
		virtual void manageLife(Life& l, bool& actualFase, int damage);

		void movement(const double& deltaTime);
		void bomberAttack(const double& deltaTime,int t1, int t2);
		void meleeAttack();
		bool inline const isMeleeing() { return ((_anim->getCurrentAnim() == AnimatedSpriteComponent::EnemyAttack) && !_anim->animationFinished()); }
		bool inline const isbeetweenFases() {return _beetwenFase;}
		void checkMelee();
		void armShoot();

		void orbAttack();

		virtual void beginCollision(GameComponent* other, b2Contact* contact);

		void Fase1(const double& deltaTime);
		void Fase2(const double& deltaTime);
		void Fase3(const double& deltaTime);
		void beetwenFases(const double& deltaTime);
		void changeFase(bool& nextFase);

		void throwBomb();
		void throwOrb();
		

};

