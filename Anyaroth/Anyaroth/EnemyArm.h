#pragma once
#include "Arm.h"

class EnemyArm : public Arm
{
private:
	GameComponent* _target;
	b2Body* _targetBody;
public:
	EnemyArm(Texture* texture, GameComponent* enemy, GameComponent* target, Game* g, PlayState* play, Vector2D offset = { 0,0 });

	void update();
};

