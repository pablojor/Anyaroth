#pragma once
#include "DistanceEnemy.h"

class ExplosiveBulletPool;
class Boss1 : public DistanceEnemy
{
	private:

		bool fase1 = true, fase2 = false;
		Vector2D _bodyPos, _prevPos, _velocity = Vector2D(0.5, 0.5), _dir = Vector2D(1,0);
		double _amplitude = 25, _damage = 50, _angularFrequency = 0.05, _k = _angularFrequency / _velocity.distance(Vector2D());

		

		//Cosas para el ataque bombardero
		ExplosiveBulletPool* _myExplosivePool = nullptr;
		Texture* _bombTexture = nullptr;
		bool bomberAttacking = false;
		int bomberAttackTime = 2500, timeOnBomberAttack = 0, timeBeetwenBombs = 0,_bombRange = 500;

	public:
		Boss1(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool, ExplosiveBulletPool* explosivePool);
		virtual ~Boss1() {};
		virtual void update(double time);

		void movement(double time);
		void bomberAttack(double time);

		void Fase1(double time);
		void Fase2(double time);
		void Fase3(double time);
		void beetwenFases(double time);


		void throwBomb();

};

