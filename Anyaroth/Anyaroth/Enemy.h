#pragma once
#include <list>
#include "GameComponent.h"

class Player;
class PlayState;

class AnimatedSpriteComponent;
class MovingComponent;
class TransformComponent;
class BodyComponent;


class Enemy : public GameComponent
{
	private:
		int _life;
	protected:
		AnimatedSpriteComponent* _anim = nullptr;
		MovingComponent* _movement = nullptr;
		TransformComponent* _transform = nullptr;
		TransformComponent* _playerTransform = nullptr;
		BodyComponent* _body = nullptr;

		PlayState* _play;
		list<GameObject*>::iterator _itList;

		bool _attacking = false;
		double _time;
		int _vision, _flipRange, _attackRange, _attackTime, _life;

	public:
		Enemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
		virtual ~Enemy() {}

    virtual void setLife(double amount);
	  virtual void addLife(double amount);
	  virtual void subLife(double amount);
	  virtual void die();

	  virtual void beginCollision(GameComponent* other);
  
		void setItList(list<GameObject*>::iterator itFR);
		virtual void update();
    
};