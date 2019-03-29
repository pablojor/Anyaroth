#pragma once
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include <vector>

typedef unsigned int uint;

class GameComponent;

struct AnimationStateImage
{
	uint name;
	uint numFrames;
	bool loop;
	bool animationFinished;
	uint lapse;
};

class AnimatedSpriteComponent : public SpriteComponent, public PhysicsComponent
{
private:
	GameComponent* _obj = nullptr;
protected:
	vector<AnimationStateImage> _animations = {};

	uint _currentAnim = 0;
	uint _frame = 0;
	double _timer = 0.0;
	bool _animationFinished = false;

public:
	enum Player { Idle, Walk, WalkBack, MeleeKnife, ReloadPistol, BeforeJump, Jump, StartFalling, Falling, Hurt, Dash, DashDown, DashBack, ReloadShotgun };
	enum Gun { None, Shoot, NoAmmo };
	enum Enemy { EnemyIdle, EnemyWalk, EnemyAttack, EnemyDie };
	enum Coin { Main };
	enum Bullet { Default };

	AnimatedSpriteComponent(GameComponent* obj) : SpriteComponent(obj), PhysicsComponent(obj), RenderComponent(obj), Component(), _obj(obj) {}
	virtual ~AnimatedSpriteComponent() {}

	virtual void render(Camera* c) const;
	virtual void update(const double& deltaTime);

	void addAnim(uint name, uint numFrames, bool loop, uint lapse = 60);
	void playAnim(uint name);

	inline bool animationFinished() { return _animations[_currentAnim].animationFinished; }
	inline uint getCurrentAnim() const { return _currentAnim; }
};