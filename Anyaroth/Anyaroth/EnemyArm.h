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
	void update(double time);
};