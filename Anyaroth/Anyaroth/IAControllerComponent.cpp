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

	if (x > 100)
	{
		_movement->changeDir(1, 0);
		_anim->playAnim("Walk");
		_anim->unFlip();
	}
	else if (x < -100)
	{
		_movement->changeDir(-1, 0);
		_anim->playAnim("Walk");
		_anim->flip();
	}
	else
	{
		_movement->changeDir(0, 0);
		_anim->playAnim("Idle");
	}
}