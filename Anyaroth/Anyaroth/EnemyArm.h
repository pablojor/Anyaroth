#pragma once
#include "Arm.h"

class EnemyArm : public Arm
{
private:
	GameComponent* _target = nullptr;
	b2Body* _targetBody = nullptr;

public:
	EnemyArm(Game* g, GameComponent* enemy, GameComponent* target, Vector2D offset = { 0,0 });
	void update(double time);
};