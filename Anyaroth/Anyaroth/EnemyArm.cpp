#include "EnemyArm.h"
#include "BodyComponent.h"
#include "DistanceEnemy.h"
#include "AnimatedSpriteComponent.h"
#include "Gun.h"

EnemyArm::EnemyArm(Game* g, GameComponent* enemy, GameComponent* target, Vector2D offset) : Arm(g, enemy, offset), _target(target)
{
	_targetBody = _target->getComponent<BodyComponent>()->getBody();
}

void EnemyArm::update(double time)
{
	GameComponent::update(time);

	if (dynamic_cast<DistanceEnemy*>(_owner)->ArmVision())
	{
		if (!dynamic_cast<DistanceEnemy*>(_owner)->getComponent<AnimatedSpriteComponent>()->isFlipped())
		{
			_anim->unFlip();
			_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());

			_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });

			lookAtTarget(Vector2D(_targetBody->GetPosition().x * 8, _targetBody->GetPosition().y * 8));
		}
		else
		{
			_anim->flip();
			_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());

			_followC->setOffset({ _followC->getInitialOffset().getX() + 8, _followC->getInitialOffset().getY() });

			lookAtTarget(Vector2D(_targetBody->GetPosition().x * 8, _targetBody->GetPosition().y * 8));
		}

	}
	else if(dynamic_cast<DistanceEnemy*>(_owner)->getComponent<AnimatedSpriteComponent>()->isFlipped())
	{
		_anim->flip();
		_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());

		_followC->setOffset({ _followC->getInitialOffset().getX() + 8, _followC->getInitialOffset().getY() });
	}
	else
	{
		_anim->unFlip();
		_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());

		_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
	}
}