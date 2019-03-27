#pragma once
#include "Arm.h"

class DistanceEnemy;

class EnemyArm : public Arm
{
private:
	GameComponent* _target = nullptr;
	b2Body* _targetBody = nullptr;
	DistanceEnemy* _myEnemy = nullptr;

public:
	EnemyArm(Game* g, GameComponent* owner, GameComponent* target, DistanceEnemy* enemy, Vector2D offset = { 0,0 });
	void update(const double& deltaTime);
	void shoot();

	inline double getAngle() const { return _transform->getRotation(); }
	inline Vector2D getPosition() const { return _transform->getPosition(); }
};