#pragma once

#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include <vector>

typedef unsigned int uint;

class GameComponent;

struct AnimationState
{
	uint name;
	uint numFrames;
	bool loop;
	bool animationFinished;
};

class AnimatedSpriteComponent : public SpriteComponent, public PhysicsComponent
{
protected:
	vector<AnimationState> _animations = {};

	uint _currentAnim = 0;

	uint _frame;
	uint _lastTimeUpdated = 0;  // last time we update a frame
	uint _freq = 100; // the frequency of updating frames

	bool _animationFinished = false;

	bool _active = true;
public:
	enum Player { Idle, Walk, WalkBack, MeleeKnife, ReloadPistol, BeforeJump, Jump, StartFalling, Falling, Hurt, Dash, DashDown, DashBack, ReloadShotgun };
	enum Gun { None, Shoot, NoAmmo };
	enum Enemy { EnemyIdle, EnemyWalk, EnemyAttack };
	enum Coin { Main };
	enum Bullet { Default };


	AnimatedSpriteComponent(GameComponent* obj);
	virtual ~AnimatedSpriteComponent();

	virtual void render(Camera* c) const;
	virtual void update();

	void addAnim(uint name, uint numFrames, bool loop);
	void playAnim(uint name);

	bool animationFinished() { return _animations[_currentAnim].animationFinished; };
	uint getCurrentAnim() { return _currentAnim; };

	void setActive(bool b) { _active = b; };
};

