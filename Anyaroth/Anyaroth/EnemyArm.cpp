#include "EnemyArm.h"



EnemyArm::EnemyArm(Texture* texture, GameComponent* enemy, GameComponent* target, Game* g, PlayState* play, Vector2D offset) : Arm(texture, enemy, g, play, offset), _target(target)
{
	_targetTransform = _target->getComponent<TransformComponent>();
}


EnemyArm::~EnemyArm()
{
}

void EnemyArm::update()
{
	GameComponent::update();

	Vector2D direction = (_transform->getPosition() - _targetTransform->getPosition());

	direction.normalize();

	//Distancia del mouse al brazo
	double distance = _targetTransform->getPosition().distance(_transform->getPosition());//sqrt(pow(_controller->mouseX - _transform->getPosition().getX(), 2) + pow(_controller->mouseY - _transform->getPosition().getY(), 2));

	//cout << distance << endl;

	//actualizo angulo del brazo
	double rot = atan2(direction.getY(), direction.getX()) * 180.0 / PI;

	if (!_anim->isFlipped())
	{
		rot -= 180;// - 10;
	}
	_transform->setRotation(rot);
}