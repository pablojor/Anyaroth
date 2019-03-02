#include "EnemyArm.h"

EnemyArm::EnemyArm(Texture* texture, GameComponent* enemy, GameComponent* target, Game* g, PlayState* play, Vector2D offset) : Arm(texture, enemy, g, play, offset), _target(target)
{
	_targetTransform = _target->getComponent<TransformComponent>();
}

void EnemyArm::update()
{
	GameComponent::update();
	
	rotate(_targetTransform->getPosition());
}

