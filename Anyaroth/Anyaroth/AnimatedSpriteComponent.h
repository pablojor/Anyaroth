#pragma once

#include "SpriteComponent.h"
#include <unordered_map>

enum Animation { Idle, Walk };

struct AnimationState {
	string name;
	uint numFrames;
};


class AnimatedSpriteComponent : public SpriteComponent
{
protected:

	//const uint NUM_ANIM = 2;

	unordered_map<string, uint> animations = { /*{"Idle",16}, {"Walk",10} */};

	string currentAnim = "";

	uint frame;

	uint _lastTimeUpdated = 0;  // last time we update a frame
	uint _freq = 50; // the frequency of updating frames
public:
	AnimatedSpriteComponent(TransformComponent* trans, Texture* _texture);
	virtual ~AnimatedSpriteComponent();
	void render() const;
	void update();

	void addAnim(string name, int numFrames);
	void playAnim(string name);
};

