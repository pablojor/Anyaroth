#pragma once

#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include <unordered_map>

class GameComponent;

struct AnimationState 
{
	string name;
	uint numFrames;
};

class AnimatedSpriteComponent: public SpriteComponent, public PhysicsComponent
{
	protected:
		unordered_map<string, uint> _animations = { /*{"Idle",16}, {"Walk",10} */};

		string _currentAnim = "";

		uint _frame;
		uint _lastTimeUpdated = 0;  // last time we update a frame
		uint _freq = 50; // the frequency of updating frames
	public:
		AnimatedSpriteComponent(GameComponent* obj);
		virtual ~AnimatedSpriteComponent();

		virtual void render() const;
		virtual void update();

		void addAnim(string name, int numFrames);
		void playAnim(string name);
};

