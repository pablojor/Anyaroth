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
};

class AnimatedSpriteComponent : public SpriteComponent, public PhysicsComponent
{
protected:
	vector<AnimationState> _animations = { /*{"Idle",16}, {"Walk",10} */ };

	uint _currentAnim = 0;

	uint _frame;
	uint _lastTimeUpdated = 0;  // last time we update a frame
	uint _freq = 50; // the frequency of updating frames

	bool _animationFinished = false;
public:
	enum Animations { Idle, Walk, WalkBack };

	AnimatedSpriteComponent(GameComponent* obj);
	virtual ~AnimatedSpriteComponent();

	virtual void render() const;
	virtual void update();

	void addAnim(Animations name, uint numFrames, bool loop);
	void playAnim(Animations name);
};

