#include "IAControllerComponent.h"
#include "GameComponent.h"
#include "Player.h"


IAControllerComponent::IAControllerComponent(GameComponent* obj) : PhysicsComponent(obj)
{
	_movement = obj->getComponent<MovingComponent>();
	if (_movement == nullptr)
		_movement = obj->addComponent<MovingComponent>();

	_anim = obj->getComponent<AnimatedSpriteComponent>();
	if (_anim == nullptr)
		_anim = obj->addComponent<AnimatedSpriteComponent>();

	_myTransform = obj->getComponent<TransformComponent>();
	if (_myTransform == nullptr)
		_myTransform = obj->addComponent<TransformComponent>();

	_meleeAttack = obj->getComponent<MeleeComponent>();
	if (_meleeAttack == nullptr)
		_meleeAttack = obj->addComponent<MeleeComponent>();
}

void IAControllerComponent::addPlayer(Player* player)
{
	_playerTransform = player->getComponent<TransformComponent>();
	if (_playerTransform == nullptr)
		_playerTransform = player->getComponent<TransformComponent>();
}

void IAControllerComponent::update()
{
	Vector2D enemy, player;

	enemy = _myTransform->getPosition();
	player = _playerTransform->getPosition();

	double x, y;

	x = player.getX() - enemy.getX();
	y = player.getY() - enemy.getY();

	if (!_attacking && x < 400 && x > - 400)
	{
		if (x > 40)
		{
			_anim->unFlip();

			if (x > 100)
			{
				_movement->changeDir(0.3, 0);
				_anim->playAnim("Walk");
			}
			else
			{
				_movement->changeDir(0, 0);
				_anim->playAnim("Idle");
				_attacking = true;
				_meleeAttack->attack();
			}
		}
		else if (x < -40)
		{
			_anim->flip();

			if (x < -100)
			{
				_movement->changeDir(-0.3, 0);
				_anim->playAnim("Walk");
			}
			else
			{
				_movement->changeDir(0, 0);
				_anim->playAnim("Idle");
				_attacking = true;
				_meleeAttack->attack();
			}
		}
	}
	else 
	{ 
		_movement->changeDir(0, 0);
		_anim->playAnim("Idle");
	}
}