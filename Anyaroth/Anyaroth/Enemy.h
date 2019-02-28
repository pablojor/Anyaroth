#pragma once
#include <list>
#include "GameComponent.h"
#include "Life.h"

class Player;
class PlayState;

class AnimatedSpriteComponent;
class MovingComponent;
class TransformComponent;
class BodyComponent;


class Enemy : public GameComponent
{
	protected:
		//Texture* _texture = nullptr;
		AnimatedSpriteComponent* _anim = nullptr;
		MovingComponent* _movement = nullptr;
		TransformComponent* _transform = nullptr;
		Player* _player = nullptr;
		BodyComponent* _body = nullptr;

		PlayState* _play;
		list<GameObject*>::iterator _itList;

		Life _life;
		bool _attacking = false;
		double _time;
		int _vision, _attackRange, _attackTime, _damage;

		double _hurtTime = 1000;
		bool _hurt = false;

	public:
		Enemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
		virtual ~Enemy() {}



		virtual void beginCollision(GameComponent* other, b2Contact* contact);

		void setItList(list<GameObject*>::iterator itFR);

		virtual inline void noLongerAttacking() { _attacking = false; }

		virtual void update();

		void die();
		void subLife(int damage);
		Life getLife() { return _life; }
};