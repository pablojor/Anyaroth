#pragma once

#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include <vector>

class GameComponent;

struct AnimationState 
{
	uint name;
	uint numFrames;
};

class AnimatedSpriteComponent: public SpriteComponent, public PhysicsComponent
{
	protected:
		vector<pair<uint, uint>> _animations = { /*{"Idle",16}, {"Walk",10} */};

		uint _currentAnim = 0;

		uint _frame;
		uint _lastTimeUpdated = 0;  // last time we update a frame
		uint _freq = 50; // the frequency of updating frames
	public:
		enum Animations { Idle, Walk, WalkBack };

		AnimatedSpriteComponent(GameComponent* obj);
		virtual ~AnimatedSpriteComponent();

		virtual void render() const;
		virtual void update();

		void addAnim(Animations name, int numFrames);
		void playAnim(Animations name);
};

