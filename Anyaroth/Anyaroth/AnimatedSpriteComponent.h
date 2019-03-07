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
	//uint lapse; //poner parametro si queremos regular la velocidad de cada animacion individualmente
};

class AnimatedSpriteComponent : public SpriteComponent, public PhysicsComponent
{
protected:
	vector<AnimationState> _animations = {};

	uint _currentAnim = 0;

	uint _frame;
	uint _lastTimeUpdated = 0;  //last time we update a frame
	uint _lapse = 60; //the frequency of updating frames

	bool _animationFinished = false;
	bool _active = true;

public:
	enum Player { Idle, Walk, WalkBack, MeleeKnife, ReloadPistol, BeforeJump, Jump, StartFalling, Falling, Hurt, Dash, DashDown, DashBack, ReloadShotgun };
	enum Gun { None, Shoot, NoAmmo };
	enum Enemy { EnemyIdle, EnemyWalk, EnemyAttack };
	enum Coin { Main };
	enum Bullet { Default };

	AnimatedSpriteComponent(GameComponent* obj) : SpriteComponent(obj), PhysicsComponent(obj), RenderComponent(obj), Component() {}
	virtual ~AnimatedSpriteComponent() {}

	virtual void render(Camera* c) const;
	virtual void update();

	void addAnim(uint name, uint numFrames, bool loop); //(.., lapse = 60) //poner parametro si queremos regular la velocidad de cada animacion individualmente
	void playAnim(uint name);

	inline bool animationFinished() { return _animations[_currentAnim].animationFinished; }
	inline uint getCurrentAnim() const { return _currentAnim; }

	inline void setActive(bool b) { _active = b; }
};