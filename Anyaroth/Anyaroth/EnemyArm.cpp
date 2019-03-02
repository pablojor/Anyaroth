#include "EnemyArm.h"

EnemyArm::EnemyArm(Texture* texture, GameComponent* enemy, GameComponent* target, Game* g, PlayState* play, Vector2D offset) : Arm(texture, enemy, g, play, offset), _target(target)
{
	_targetTransform = _target->getComponent<TransformComponent>();
}

void EnemyArm::update()
{
	GameComponent::update();
	
	if (_targetTransform->getPosition().getX() > _transform->getPosition().getX())
	{
		_anim->unFlip();
		_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());

		_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
	}
	else
	{
		_anim->flip();
		_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());

		_followC->setOffset({ _followC->getInitialOffset().getX() + 8, _followC->getInitialOffset().getY() });
	}
	rotate(_targetTransform->getPosition());
}

