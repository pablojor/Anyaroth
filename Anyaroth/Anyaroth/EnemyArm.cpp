#include "EnemyArm.h"
#include "BodyComponent.h"
#include "DistanceEnemy.h"
#include "AnimatedSpriteComponent.h"
#include "Gun.h"

EnemyArm::EnemyArm(Game* g, GameComponent* owner, GameComponent* target, DistanceEnemy* enemy, Vector2D offset) : Arm(g, owner, offset), _target(target)
{
	_targetBody = _target->getComponent<BodyComponent>()->getBody();
	_myEnemy = enemy;
}

void EnemyArm::update(double time)
{
	GameComponent::update(time);

	if (_myEnemy->ArmVision())
	{
		if (!_myEnemy->getComponent<AnimatedSpriteComponent>()->isFlipped())
		{
			
			_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());

			_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });

			lookAtTarget(Vector2D(_targetBody->GetPosition().x * 8, _targetBody->GetPosition().y * 8));
			_anim->unFlip();
		}
		else
		{
			
			_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());

			_followC->setOffset({ _followC->getInitialOffset().getX() + 8, _followC->getInitialOffset().getY() });
			_transform->setRotation(_transform->getRotation() + 180);

			lookAtTarget(Vector2D(_targetBody->GetPosition().x * 8, _targetBody->GetPosition().y * 8));
			_anim->flip();
		}

	}
	else if(_myEnemy->getComponent<AnimatedSpriteComponent>()->isFlipped())
	{
		_anim->flip();
		_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());

		_transform->setRotation(_transform->getRotation() + 180);
		_followC->setOffset({ _followC->getInitialOffset().getX() + 8, _followC->getInitialOffset().getY() });
	}
	else
	{
		_anim->unFlip();
		_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());

		_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
	}
}